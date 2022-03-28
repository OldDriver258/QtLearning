#include "clipboarddemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClipboardDemo demo;
    demo.show();
    return a.exec();
}
