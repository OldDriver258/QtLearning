#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if 1
    QFile data("file.txt");
    if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&data);
        out << "The answer is " << 42;
    }
#else
    QFile data("file.txt");
    if (data.open(QFile::ReadOnly)) {
        QTextStream in(&data);
        QString str;
        int ans = 0;
        in >> str >> ans;
    }
#endif

    return a.exec();
}
