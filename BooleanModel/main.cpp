#include "booleanwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BooleanWindow w;
    w.show();
    return a.exec();
}
