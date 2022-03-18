#include "mainwindow.h"

#include <QApplication>
#include <QListIterator>
#include <QDebug>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

#if 0
    QList<QString> list_str;
    list_str << "A" << "B" << "C" << "D";

    QListIterator<QString> iterator(list_str);
    while (iterator.hasNext()) {
        qDebug() << iterator.next();
    }

    QList<int>  list_int;
    list_int << 1 << 2 << 3 << 4;

    QMutableListIterator<int> iterator_int(list_int);
    while (iterator_int.hasNext()) {
        if (iterator_int.next() % 2 != 0) {
            iterator_int.remove();
        }
    }
    iterator_int.toFront();
    while (iterator_int.hasNext()) {
        qDebug() << iterator_int.next();
    }
#else
    QList<QString> list_str;
    list_str << "A" << "B" << "C" << "D";

    QList<QString>::iterator i;
    for (i = list_str.begin(); i != list_str.end(); i++) {
        *i = (*i).toLower();
        qDebug() << *i;
    }

    QString str;
    foreach (str, list_str) {
        qDebug() << str;
    }
#endif
    return a.exec();
}
