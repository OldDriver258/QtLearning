#include <QLabel>
#include <QListWidget>
#include <QBoxLayout>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *w = new QWidget(this);
    label = new QLabel(this);
    label->setFixedWidth(70);

    listWidget = new QListWidget(this);

    new QListWidgetItem(QIcon(":/image/chrome.png"), tr("Chrome"), listWidget);
    new QListWidgetItem(QIcon(":/image/firefox.png"), tr("Firefox"), listWidget);

    listWidget->addItem(new QListWidgetItem(QIcon(":/image/ie.jpg"), tr("IE")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/image/netscape.png"), tr("Netscape")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/image/opera.png"), tr("Opera")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/image/Safari.png"), tr("Safari")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/image/TheWorld.png"), tr("TheWorld")));
    listWidget->addItem(new QListWidgetItem(QIcon(":/image/Traveler.jpg"), tr("Traveler")));

    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setIcon(QIcon(":/image/Maxthon.jpg"));
    newItem->setText(tr("Maxthon"));
    listWidget->insertItem(3, newItem);

    QHBoxLayout *layout = new QHBoxLayout(w);
    layout->addWidget(label);
    layout->addWidget(listWidget);

    listWidget->setViewMode(QListView::IconMode);

    setCentralWidget(w);

    connect(listWidget, SIGNAL(currentTextChanged(QString)),
            label,      SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
}

