#include <QGraphicsScene>
#include <QTimer>
#include <QEvent>
#include <QKeyEvent>
#include <QtDebug>
#include <QMessageBox>

#include "food.h"
#include "snake.h"
#include "gamecontroller.h"

GameController::GameController(QGraphicsScene &scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(*this)),
    isPause(false)

{
    timer.start(1000 / 33);

    Food *al = new Food(0, -50);
    scene.addItem(al);

    scene.addItem(snake);

    scene.installEventFilter(this);

    //resume(); // 初始化 GameController 的时候, resumeAction 还没有初始化
    //通过定时器的tick推荐 scene 进行 advance. 场景发生升级会推进 item 也会对应 advance
    connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
}

void GameController::handleKeyPressed(QKeyEvent *event)
{
    qDebug() << "get key event " << event;
    if (!isPause)
        switch (event->key()) {

        case Qt::Key_Left:
            snake->setMoveDirection(Snake::MoveLeft);
            break;

        case Qt::Key_Right:
            snake->setMoveDirection(Snake::MoveRight);
            break;

        case Qt::Key_Up:
            snake->setMoveDirection(Snake::MoveUp);
            break;

        case Qt::Key_Down:
            snake->setMoveDirection(Snake::MoveDown);
            break;

        case Qt::Key_Space:
            pause();
            break;
        }
    else resume();
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;

    addNewFood();
}

void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int)(qrand() % 200 - 100) / 10;
        y = (int)(qrand() % 200 - 100) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x, y);
    scene.addItem(food);
}

void GameController::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0, this, SLOT(gameOver()));
}

void GameController::gameOver()
{
    disconnect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    if (QMessageBox::Yes == QMessageBox::information(NULL,
                            tr("Game Over"), tr("Again?"),
                            QMessageBox::Yes | QMessageBox::No,
                            QMessageBox::Yes)) {
        connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
        scene.clear();

        qDebug() << "game over";

        snake = new Snake(*this);
        scene.addItem(snake);
        addNewFood();
    } else {
        exit(0);
    }
}

void GameController::pause()
{
    disconnect(&timer, SIGNAL(timeout()),
               &scene, SLOT(advance()));
    isPause = true;
    setResume();
}

void GameController::resume()
{
    connect(&timer, SIGNAL(timeout()),
            &scene, SLOT(advance()));
    isPause = false;
    setResume();
}

bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}
