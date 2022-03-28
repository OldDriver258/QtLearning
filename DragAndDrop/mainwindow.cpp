#include "mainwindow.h"
#include <QDragEnterEvent>
#include <QLayout>
#include <QUrl>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    textEdit = new QTextEdit(this);
    textEdit->setAcceptDrops(true);

    listWidget[0] = new ProjectListWidget(this);
    listWidget[1] = new ProjectListWidget(this);

    new QListWidgetItem(tr("Oak"), listWidget[0]);
    new QListWidgetItem(tr("Fir"), listWidget[0]);
    new QListWidgetItem(tr("Pine"), listWidget[0]);

    QHBoxLayout *listLayout = new QHBoxLayout(this);
    listLayout->addWidget(listWidget[0]);
    listLayout->addWidget(listWidget[1]);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    layout->addLayout(listLayout);

    QWidget *w = new QWidget();
    w->setLayout(layout);
    setCentralWidget(w);

    setWindowTitle(tr("Text Editor"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    // 当拖动对象是个 text/uri-list 数据（即文件名），我们便接受这个动作
    if (event->mimeData()->hasFormat("text/uri-list")) {
        // 向用户表示推动对象可以放在这个组件上
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    // 有可能是多个文件一起拖动
    QList<QUrl> urls = event->mimeData()->urls();
    if (urls.isEmpty()) {
        return;
    }

    // 我们只处理第一个文件
    QString fileName = urls.first().toLocalFile();
    if (fileName.isEmpty()) {
        return;
    }

    if (readFile(fileName)) {
        setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
    }
}

bool MainWindow::readFile(const QString &fileName)
{
    bool r = false;
    QFile file(fileName);
    QString content;

    if (file.open(QIODevice::ReadOnly)) {
        content = file.readAll();
        r = true;
    }
    textEdit->setText(content);

    return r;
}

