#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
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
}

void MainWindow::open()
{
    QMessageBox msgbox;
    msgbox.setText(tr("The document has been modified."));
    msgbox.setInformativeText(tr("Do you want to save changes?"));
    msgbox.setDetailedText(tr("Differences here..."));
    msgbox.setStandardButtons(QMessageBox::Save
                              | QMessageBox::Discard
                              | QMessageBox::Cancel);
    msgbox.setDefaultButton(QMessageBox::Save);
    int ret = msgbox.exec();
    switch (ret) {

    case QMessageBox::Save:
        qDebug() << "Save document!";
        break;

    case QMessageBox::Discard:
        qDebug() << "Discard changes!";
        break;

    case QMessageBox::Cancel:
        qDebug() << "Close document!";
        break;
    }
}
