#include <QGraphicsScene>
#include <QTimer>

#include "gamecontroller.h"

GameController::GameController(QGraphicsScene *scene, QObject *parent) :
    QObject(parent),
    scene(scene),
    snake(new Snake(this))
{
    timer.start(1000 / 33);

    Food *al = new Food(0, -50);
    scene->addItem(al);

    scene->addItem(snake);

    scene->installEventFilter(this);

    resume();
}

