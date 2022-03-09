#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintedWidget painter;
    painter.show();

    return a.exec();
}
