#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

class QGraphicsScene;
class QTimer;
class Snake;

class GameController
{
public:
    GameController(QGraphicsScene *scene, QObject *parent = 0);

private:
    QTimer timer;
    QGraphicsScene &scene;
    Snake *snake;
};

#endif // GAMECONTROLLER_H
