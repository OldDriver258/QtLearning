#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.readFile("../DOM_XmlReader/books.xml");
    w.show();
    return a.exec();
}
