#include "mainwindow.h"

#include <QApplication>
#include <QDate>
#include <QList>
#include <QDataStream>

struct Movie
{
    int     id;
    QString title;
    QDate   releaseDate;
};

QDataStream &operator<<(QDataStream &out, const Movie &movie)
{
    out << (quint32)movie.id << movie.title << movie.releaseDate;
    return out;
}

QDataStream &operator>>(QDataStream &in, Movie &movie)
{
    quint32     id;
    QDate       date;
    QString     str;

    in >> id >> str >> movie;
    movie.id = (int)id;
    movie.releaseDate = date;
    movie.title = str;
    return in;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QList<Movie>    movs;

    Movie

    return a.exec();
}
