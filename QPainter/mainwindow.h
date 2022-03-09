#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QDebug>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

class PaintedWidget : public QWidget
{
    Q_OBJECT

public:
    PaintedWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // MAINWINDOW_H
