#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
//    ui->setupUi(this);

    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open.jpg"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    statusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
//    QDialog dialog(this);
//    dialog.setWindowTitle(tr("Hello, dialog!"));
//    dialog.exec();
//    qDebug() << dialog.result();

    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Question"),
                                                  tr("Are you OK?"),
                                                  QMessageBox::Yes | QMessageBox::No,
                                                  QMessageBox::Yes)) {
        QMessageBox::information(this, tr("Hmm..."), tr("I'm glad to hear that"));
    } else {
        QMessageBox::information(this, tr("Hmm..."), tr("I'm sorry"));
    }
}
