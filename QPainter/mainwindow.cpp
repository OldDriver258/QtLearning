#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

PaintedWidget::PaintedWidget(QWidget *parent)
    :QWidget(parent)
{
    resize(800, 600);
    setWindowTitle(tr("Paint Demo"));
}

#define Painter_Demo            0
#define Painter_Antialiasing    0
#define Painter_Gradient        0
#define Painter_Coordinate      1

/*
 * paintEvent() 作为重绘函数，会在需要重绘时由 Qt 自动调用。
 * "需要重绘"可能发生在很多地方，比如组件刚刚创建出来的时候就需要重绘；
 * 组件最大化、最小化的时候也需要重新绘制；组件由遮挡变成完全显示的时候也需要等等。
 */
void PaintedWidget::paintEvent(QPaintEvent *)
{
    static int count;
    QPainter painter(this);
#if Painter_Demo >0
    painter.drawLine(80, 100, 650, 500);
    painter.setPen(Qt::red);
    painter.drawRect(10, 10, 100, 400);
    painter.setPen(QPen(Qt::green, 5));
    painter.setBrush(Qt::blue);
    painter.drawEllipse(50, 150, 400, 200);
#elif Painter_Antialiasing > 0
    painter.setPen(QPen(Qt::black, 10, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(50, 150, 400, 300);

    painter.setRenderHint(QPainter::Antialiasing, true); // 这句话开启了反锯齿功能
    painter.setPen(QPen(Qt::black, 10, Qt::DashDotLine, Qt::RoundCap));
    painter.setBrush(Qt::yellow);
    painter.drawEllipse(550, 150, 400, 300);
#elif Painter_Gradient > 0
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int r = 300;
    QConicalGradient conicalGradient(0, 0, 0);
    conicalGradient.setColorAt(0.0, Qt::red);
    conicalGradient.setColorAt(60.0/360.0, Qt::yellow);
    conicalGradient.setColorAt(120.0/360.0, Qt::green);
    conicalGradient.setColorAt(180.0/360.0, Qt::cyan);
    conicalGradient.setColorAt(240.0/360.0, Qt::blue);
    conicalGradient.setColorAt(300.0/360.0, Qt::magenta);
    conicalGradient.setColorAt(1.0, Qt::red);

    painter.translate(r, r);

    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    painter.drawEllipse(QPoint(0, 0), r, r);
#elif Painter_Coordinate > 0
    painter.fillRect(10, 10, 50, 100, Qt::red);

    painter.save(); //这里保存了 painter 默认的状态, 通过后面的 restore 恢复默认的位置关系
    painter.translate(100, 0);
    painter.fillRect(10, 10, 50, 100, Qt::yellow);

    painter.restore();
    painter.save();
    painter.translate(300, 0);
    painter.rotate(30);
    painter.fillRect(10, 10, 50, 100, Qt::green);

    painter.restore();
    painter.save();
    painter.translate(400, 0);
    painter.scale(2, 3);
    painter.fillRect(10, 10, 50, 100, Qt::blue);

    painter.restore();
    painter.save();
    painter.translate(600, 0);
    painter.shear(0, 1);
    painter.fillRect(10, 10, 50, 100, Qt::cyan);
    painter.restore();
#endif
    qDebug() << "paintEvent" << count++;
}
