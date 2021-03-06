#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "projectlistwidget.h"
#include <QMainWindow>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    bool readFile(const QString &fileName);
    QTextEdit *textEdit;
    ProjectListWidget *listWidget[2];
};
#endif // MAINWINDOW_H
