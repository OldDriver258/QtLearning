#include "mainwindow.h"

#include <QApplication>
#include <QDate>
#include <QList>
#include <QDataStream>
#include <QDebug>

struct Movie
{
    int     id;
    QString title;
    QDate   releaseDate;
};

QDebug operator<<(QDebug out, const Movie &movie)
{
    out << (quint32)movie.id << movie.title << movie.releaseDate;
    return out;
}

//QDebug &operator>>(QDebug &in, Movie &movie)
//{
//    quint32     id;
//    QDate       date;
//    QString     str;

//    in >> id >> str >> movie;
//    movie.id = (int)id;
//    movie.releaseDate = date;
//    movie.title = str;
//    return in;
//}
p

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<Movie>    movs;

    Movie mov;
    mov.id = 15;
    mov.releaseDate = QDate(2021, 3, 12);
    mov.title = "Hello";

    qDebug() << mov;

    return a.exec();
}
