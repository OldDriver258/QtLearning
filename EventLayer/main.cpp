#include "mainwindow.h"
#include <QApplication>

/*
 * 现在我们可以总结一下 Qt 的事件处理，实际上是有五个层次：
 * 1.重写paintEvent()、mousePressEvent()等事件处理函数。这是最普通、最简单的形式，同时功能也最简单。
 * 2.重写event()函数。event()函数是所有对象的事件入口，QObject和QWidget中的实现，
 *   默认是把事件传递给特定的事件处理函数。
 * 3.在特定对象上面安装事件过滤器。该过滤器仅过滤该对象接收到的事件。
 * 4.在QCoreApplication::instance()上面安装事件过滤器。
 *   该过滤器将过滤所有对象的所有事件，因此和notify()函数一样强大，但是它更灵活，因为可以安装多个过滤器。
 *   全局的事件过滤器可以看到 disabled 组件上面发出的鼠标事件。全局过滤器有一个问题：只能用在主线程。
 * 5.重写QCoreApplication::notify()函数。这是最强大的，和全局事件过滤器一样提供完全控制，
 *   并且不受线程的限制。但是全局范围内只能有一个被使用（因为QCoreApplication是单例的）。
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Label label;
    a.installEventFilter(new EventFilter(&label, &label));
    label.show();

    return a.exec();
}
