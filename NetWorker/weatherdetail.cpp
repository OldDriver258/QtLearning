#include "weatherdetail.h"

QDebug operator<<(QDebug dbg, const WeatherDetail &w)
{
    dbg.nospace() << "("
                  << "Description: " << w.desc() << "; "
                  << "Icon: " << w.icon()
                  << ")";
    return dbg.space();
}

WeatherDetail::WeatherDetail()
{

}

QString &WeatherDetail::desc() const
{
    static QString desc;

    return desc;
}

void WeatherDetail::setDesc(const QString &desc)
{
    QString &str = WeatherDetail::desc();
    str = desc;
}

QString &WeatherDetail::icon() const
{
    static QString icon;

    return icon;
}

void WeatherDetail::setIcon(const QString &icon)
{
    QString &str = WeatherDetail::icon();
    str = icon;
}

QDebug operator <<(QDebug dbg, const WeatherInfo &w)
{
    dbg.nospace() << "("
                  << "id: " << w.id() << "; "
                  << "City name: " << w.cityName() << "; "
                  << "Date time: " << w.dateTime().toString(Qt::DefaultLocaleLongDate) << ": " << endl
                  << "Temperature: " << w.temperature() << ", "
                  << "Pressure: " << w.pressure() << ", "
                  << "Humidity: " << w.humidity() << endl
                  << "Details: [";
    foreach (WeatherDetail *detail, w.details()) {
        dbg.nospace() << "( Description: " << detail->desc() << ", "
                      << "Icon: " << detail->icon() << "), ";
    }
    dbg.nospace() << "] )";
    return dbg.space();
}

WeatherInfo::WeatherInfo()
{

}

QString &WeatherInfo::cityName() const
{
    static QString cityName;

    return cityName;
}

void WeatherInfo::setCityName(const QString &cityName)
{
    QString &str = WeatherInfo::cityName();
    str = cityName;
}

quint32 &WeatherInfo::id() const
{
    static quint32 id;

    return id;
}
void WeatherInfo::setId(quint32 id)
{
    quint32 &data = WeatherInfo::id();
    data = id;
}

QDateTime &WeatherInfo::dateTime() const
{
    static QDateTime dateTime;

    return dateTime;
}

void WeatherInfo::setDateTime(const QDateTime &dateTime)
{
    QDateTime &time = WeatherInfo::dateTime();
    time = dateTime;
}

float &WeatherInfo::temperature() const
{
    static float temperature;

    return temperature;
}

void WeatherInfo::setTemperature(float temperature)
{
    float &temp = WeatherInfo::temperature();
    temp = temperature;
}

float &WeatherInfo::humidity() const
{
    static float humidity;

    return humidity;
}

void WeatherInfo::setHumidity(float humidity)
{
    float &humid = WeatherInfo::humidity();
    humid = humidity;
}

float &WeatherInfo::pressure() const
{
    static float pressure;

    return pressure;
}

void WeatherInfo::setPressure(float pressure)
{
    float &press = WeatherInfo::pressure();
    press = pressure;
}

QList<WeatherDetail *> &WeatherInfo::details() const
{
    static QList<WeatherDetail *> details;

    return details;
}

void WeatherInfo::setDetails(const QList<WeatherDetail *> details)
{
    QList<WeatherDetail *> &det = WeatherInfo::details();
    det = details;
}
