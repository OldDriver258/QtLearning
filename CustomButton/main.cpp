#include <QApplication>
#include "custonbutton.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CustomButton btn;
    btn.setText("This is a Button");
    btn.show();

    return a.exec();
}
