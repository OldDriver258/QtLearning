#include "mainwindow.h"

#include <QTableWidget>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QItemSelection>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    tableWidget = new QTableWidget(8, 4, this);
    setCentralWidget(tableWidget);

    QItemSelectionModel *selectionModel = tableWidget->selectionModel();

    connect(selectionModel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,           SLOT(updateSelection(QItemSelection,QItemSelection)));
    connect(selectionModel, SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,           SLOT(changeCurrent(QModelIndex,QModelIndex)));

    QModelIndex topLeft = tableWidget->model()->index(0, 0);
    QModelIndex bottomRight = tableWidget->model()->index(5, 2);

    //通过两个 index 确定一个选区
    QItemSelection selection(topLeft, bottomRight);
    selectionModel->select(selection, QItemSelectionModel::Select);

    QItemSelection toggleSelection;
    topLeft = tableWidget->model()->index(2, 1);
    bottomRight = tableWidget->model()->index(7, 3);
    toggleSelection.select(topLeft, bottomRight);
    selectionModel->select(toggleSelection, QItemSelectionModel::Toggle);
}

MainWindow::~MainWindow()
{
}

void MainWindow::updateSelection(const QItemSelection &selected,
                                 const QItemSelection &deselected)
{
    QModelIndex index;
    QModelIndexList items = selected.indexes();

    foreach (index, items) {
        QString text = QString("(%1, %2)").arg(index.row()).arg(index.column());
        tableWidget->model()->setData(index, text);
    }

    items = deselected.indexes();

    foreach (index, items) {
        tableWidget->model()->setData(index, "");
    }
}

void MainWindow::changeCurrent(const QModelIndex &current,
                               const QModelIndex &previous)
{
    statusBar()->showMessage(tr("Moved from (%1, %2) to (%3, %4)")
                             .arg(previous.row()).arg(previous.column())
                             .arg(current.row()).arg(current.column()));
}



