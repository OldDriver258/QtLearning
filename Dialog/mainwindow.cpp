#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QDebug>
#include <QMessageBox>
#include <QSpinBox>

class UserAgeDialog : QDialog
{
    int  newAge;
    void accept();

Q_SIGNALS:
    void userAgeChanged(int age);
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowTitle(tr("Main Window"));

    openAction = new QAction(QIcon(":/images/doc-open.jpg"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(showUserAgeDialog()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    QToolBar *toolBar2 = addToolBar(tr("Tool Bar 2"));
    toolBar2->addAction(openAction);

    statusBar();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showUserAgeDialog()
{
    UserAgeDialog *dialog = new UserAgeDialog(this);
    QSpinBox *spinBox = new QSpinBox(dialog);
    spinBox->setRange(0, 130);
    connect(dialog, SIGNAL(userAgeChanged()), this, SLOT(setUserAge));
    dialog->show();
}

void MainWindow::setUserAge(int age)
{
    userAge = age;
}

void UserAgeDialog::accept()
{
    emit userAgeChanged(newAge);
    QDialog::accept();
}
