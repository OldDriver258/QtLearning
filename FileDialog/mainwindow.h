#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTextEdit>
#include <QMainWindow>
#include <QCloseEvent>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void closeEvent(QCloseEvent *event);

private slots:
    void openFile(void);
    void saveFile(void);
    void mysetWindowModified(void);

private:
    QAction *openAction, *saveAction;
    QTextEdit *textEdit;
};

#endif // MAINWINDOW_H
