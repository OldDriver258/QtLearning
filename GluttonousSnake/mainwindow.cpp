#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractScrollArea>

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
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    resize(1000, 1000);
//    setFixedSize(600, 700);

    createActions();
    createMenus();
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
    scene->setSceneRect(-100, -100, 200 + 10, 200 + 10);
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
    //配置窗口拉伸是, 显示的比例不变
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::createActions()
{
    newGameAction = new QAction(tr("&New Game"), this);
    newGameAction->setShortcut(QKeySequence::New);
    newGameAction->setStatusTip(tr("Start a new game"));
    connect(newGameAction, SIGNAL(triggered()), this, SLOT(newGame()));

    exitAction = new QAction(tr("&Exit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the game"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    pauseAction = new QAction(tr("&Pause"), this);
    pauseAction->setStatusTip(tr("Pause..."));
    connect(pauseAction, SIGNAL(triggered()), game, SLOT(pause()));

    resumeAction = new QAction(tr("&Resume"), this);
    resumeAction->setStatusTip(tr("Resume..."));
    resumeAction->setEnabled(false);
    game->setResumeAction(resumeAction);
    connect(resumeAction, SIGNAL(triggered()), game, SLOT(resume()));

    gameHelpAction = new QAction(tr("Game &Help"), this);
    gameHelpAction->setShortcut(tr("Ctrl+H"));
    gameHelpAction->setStatusTip(tr("Help on this game"));
    connect(gameHelpAction, SIGNAL(triggered()), this, SLOT(gameHelp()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's about box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

//    aboutQtAction = new QAction(tr("About &Qt"), this);
//    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
//    connect(aboutQtAction, SIGNAL(triggered()), qApp, QApplication::aboutQt);
}

void MainWindow::createMenus()
{
    QMenu *options = menuBar()->addMenu(tr("&Options"));

    options->addAction(newGameAction);
    options->addSeparator();
    options->addAction(pauseAction);
    options->addAction(resumeAction);
    options->addSeparator();
    options->addAction(exitAction);

    QMenu *help = menuBar()->addMenu(tr("&Help"));
    help->addAction(gameHelpAction);
    help->addAction(aboutAction);
//	help->addAction(aboutQtAction);
}

void MainWindow::newGame()
{
    qDebug() << "newGame";
    QTimer::singleShot(0, game, SLOT(gameOver()));
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About this Game"), tr("<h2>Snake Game</h2>"
        "<p>Copyright &copy; XXX."
        "<p>This game is a small Qt application. It is based on the demo in the GitHub written by Devbean."));
}

void MainWindow::gameHelp()
{
    QMessageBox::about(this, tr("Game Help"), tr("Using direction keys to control the snake to eat the food"
        "<p>Space - pause & resume"));
}
