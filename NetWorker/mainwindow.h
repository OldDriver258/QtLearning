#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QEventLoop>
#include "networker.h"

enum RemoteRequest {
    FetchWeatherInfo,
    FetchWeatherIcon
};

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
    Private(MainWindow *q)
        : mainWindow(q)
    {
        netWorker = NetWorker::instance();
    }

    void fetchWeather(const QString &cityName, const QString &appid)
    {
        QNetworkReply *reply = netWorker->get(QString("https://api.openweathermap.org/data/2.5/weather?"
                                                       "q=%1&"
                                                       "mode=json&"
                                                       "units=metric&"
                                                       "lang=zh_cn&"
                                                       "appid=%2")
                                                        .arg(cityName).arg(appid));
        replyMap.insert(reply, FetchWeatherInfo);
    }

    void fetchIcon(const QString &iconName)
    {
        QEventLoop eventLoop;
        connect(netWorker,  &NetWorker::finished,
                &eventLoop, &QEventLoop::quit);

        QNetworkReply *reply = netWorker->get(QString("https://openweathermap.org/img/w/%1.png")
                                              .arg(iconName));
        replyMap.insert(reply, FetchWeatherIcon);

        eventLoop.exec();
    }

    NetWorker *netWorker;
    MainWindow *mainWindow;
    QMap<QNetworkReply *, RemoteRequest> replyMap;
};

#endif // MAINWINDOW_H
