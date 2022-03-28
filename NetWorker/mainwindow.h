#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "networker.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    class Private;
    friend class Private;
    Private *d;

};

class MainWindow::Private
{
public:
    Private()
    {
        netWorker = NetWorker::instance();
    }

    void fetchWeather(const QString &cityName, const QString &appid) const
    {
        netWorker->get(QString("https://api.openweathermap.org/data/2.5/weather?"
                               "q=%1&"
                               "mode=json&"
                               "units=metric&"
                               "lang=zh_cn&"
                               "appid=%2")
                                .arg(cityName).arg(appid));
    }

    NetWorker *netWorker;
};

#endif // MAINWINDOW_H
