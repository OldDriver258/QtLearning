#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "constants.h"
#include "gamecontroller.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      scene(new QGraphicsScene(this)),
      view(new QGraphicsView(scene, this)),
      game(new GameController(*scene, this))
{
    setCentralWidget(view);
    setFixedSize(600, 600);

    initScene();
    initSceneBackground();

    /*
     * 将调整视窗大小添加到处理事件的列表中,等待下一次时间循环去调用
     * 我们需要在视图绘制完毕后才去改变大小（视图绘制当然是在paintEvent()事件中）
     * 因此我们需要在下一次事件循环中调用adjustViewSize()函数
     */
    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::initScene()
{
    scene->setSceneRect(-100, -100, 200, 200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    QPainter p(&bg);
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::adjustViewSize()
{

}
