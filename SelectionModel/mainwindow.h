#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTableWidget;
class QItemSelection;
class QModelIndex;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateSelection(const QItemSelection &selected,
                         const QItemSelection &deselected);
    void changeCurrent(const QModelIndex &current,
                       const QModelIndex &previous);

private:
    QTableWidget *tableWidget;
};
#endif // MAINWINDOW_H
