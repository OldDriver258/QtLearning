#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QTimer;
class Snake;
class QKeyEvent;
class Food;

class GameController : public QObject
{
public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);

    void snakeAteFood(Snake *snake, Food *food);
    void snakeAteItself(Snake *snake);

public slots:
    void pause(void);
    void resume(void);
    void gameOver(void);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();
    QTimer          timer;
    QGraphicsScene &scene;
    Snake          *snake;
};

#endif // GAMECONTROLLER_H
