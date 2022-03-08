#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setUserAge(int age);

private slots:
    void showUserAgeDialog();

private:
    Ui::MainWindow *ui;
    QAction *openAction;
    int userAge;
};

#endif // MAINWINDOW_H
