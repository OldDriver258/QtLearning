#include "mainwindow.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QDebug>

const char *KEY_SHARED_MEMORY = "Shared";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      sharedMemory(new QSharedMemory(KEY_SHARED_MEMORY, this))
{
    QWidget *mainWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    setCentralWidget(mainWidget);

    QPushButton *saveButton = new QPushButton(tr("Save"), this);
    mainLayout->addWidget(saveButton);
    QHBoxLayout *picLayout = new QHBoxLayout;
    QLabel *picLabel = new QLabel(this);
    picLayout->addWidget(picLabel);
    QLabel *picLabel2 = new QLabel(this);
    picLayout->addWidget(picLabel2);
    mainLayout->addLayout(picLayout);
    QPushButton *loadButton = new QPushButton(tr("Load"), this);
    mainLayout->addWidget(loadButton);

    connect(saveButton, &QPushButton::clicked,
            [=]() {
        if (sharedMemory->isAttached()) {
            sharedMemory->detach();
        }
        /*
         * 读取文件并且显示
         */
        QString fileName = QFileDialog::getOpenFileName(this);
        QPixmap pixmap(fileName);
        picLabel->setPixmap(pixmap);
        /*
         * 图片数据存到buffer
         */
        QBuffer buffer;
        QDataStream out(&buffer);
        buffer.open(QBuffer::ReadWrite);
        out << pixmap;
        /*
         * 图片数据从buffer拷贝到共享内存中
         */
        int size = buffer.size();
        if (!sharedMemory->create(size)) {
            qDebug() << tr("Create Error: ") << sharedMemory->errorString();
        } else {
            sharedMemory->lock();
            char *to = static_cast<char *>(sharedMemory->data());
            const char *from = buffer.data().constData();
            memcpy(to, from, qMin(size, sharedMemory->size()));
            sharedMemory->unlock();
        }
    });

    connect(loadButton, &QPushButton::clicked,
            [=]() {
        sharedMemory->attach();
        if(sharedMemory->error()!=QSharedMemory::NoError) {
            qDebug() << tr("Attach Error: ") << sharedMemory->errorString();
        } else {
            QBuffer buffer;
            QDataStream in(&buffer);
            QPixmap pixmap;

            sharedMemory->lock();
            buffer.setData(static_cast<const char*>(sharedMemory->constData()), sharedMemory->size());
            sharedMemory->unlock();
            sharedMemory->detach();

            buffer.open(QBuffer::ReadWrite);
            in >> pixmap;
            picLabel2->setPixmap(pixmap);
        }
    });
}

MainWindow::~MainWindow()
{
}

