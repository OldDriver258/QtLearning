#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>

class GameController;

class Snake : public QGraphicsItem
{
public:
    enum Direction {
        NoMove,
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown
    };

    Snake(GameController &controller);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void setMoveDirection(Direction direction);
    Direction currentDirection();

    void advance(int phase);

private:
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void handleCollisions();

    QPointF         head;
    int             growing;
    int             speed;
    int             tickCounter;
    QList<QPointF>  tail;
    Direction       moveDirection;
    GameController &controller;
};

#endif // SNAKE_H
