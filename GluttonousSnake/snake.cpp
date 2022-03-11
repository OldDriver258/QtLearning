#include <QPainter>
#include <QList>
#include <QtDebug>

#include "constants.h"
#include "gamecontroller.h"
#include "food.h"
#include "snake.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameController &controller) :
    head(0, 0),
    growing(7),
    speed(5),
    moveDirection(NoMove),
    controller(controller)
{
}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    return QRectF(tl.x(),  // x
                  tl.y(),  // y
                  br.x() - tl.x() + SNAKE_SIZE,
                  br.y() - tl.y() + SNAKE_SIZE);
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
    }

    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->fillPath(shape(), Qt::yellow);

    painter->restore();
}

void Snake::setMoveDirection(Direction direction)
{
    if (moveDirection == MoveLeft && direction == MoveRight)
        return;
    if (moveDirection == MoveRight && direction == MoveLeft)
        return;
    if (moveDirection == MoveUp && direction == MoveDown)
        return;
    if (moveDirection == MoveDown && direction == MoveUp)
        return;
    moveDirection = direction;
    qDebug() << "direction " << direction;
}

Snake::Direction Snake::currentDirection()
{
    return moveDirection;
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100) {
        head.rx() = 100;
    }
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    if (head.rx() > 100) {
        head.rx() = -100;
    }
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    if (head.ry() < -100) {
        head.ry() = 100;
    }
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    if (head.ry() > 100) {
        head.ry() = -100;
    }
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    foreach(QGraphicsItem *collidingItem, collisions) {
        if(collidingItem->data(GD_Type) == GO_Food) {
            // Let GameController handle the event by putting another apple
            controller.snakeAteFood(this, (Food *)collidingItem);
            growing += 1;
        }
    }

    // Check snake eating itself
    if (tail.contains(head)) {
        controller.snakeAteItself(this);
    }
}

/*
 * 场景发生的 advance 会推动 item 也进行 advance.
 * item 的 advance 会发生两次调用第一次 phase == 0, 第二次 phase == 1, 可以通过这个机制实现一些动画
 */
void Snake::advance(int phase)
{
    //每次场景更新 item 只实现一次
    if (!phase)
        return;

    //速度控制, 多少个 tick 更新一次 snake 状态
    if (tickCounter++ % speed != 0)
        return;

    //默认状态下不发生移动, 也不用更新 snake 状态
    if (moveDirection == NoMove)
        return;

    //growing 表示 snake 的初始长度和要伸长的长度, 之前 head 的点就作为新的身体
    if (growing > 0) {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        //不需要伸长的情况下, 去掉链表头的一个数据, 也就是 snake 的最后一个点
        tail.takeFirst();
        tail << head;
    }

    //根据移动的方向给 snake 的 head 一个新的坐标
    switch (moveDirection) {

    case MoveLeft:
        moveLeft();
        break;

    case MoveRight:
        moveRight();
        break;

    case MoveUp:
        moveUp();
        break;

    case MoveDown:
        moveDown();
        break;
    }

    //设置 item 的新的位置
    setPos(head);
    //进行碰撞的检测和处理
    handleCollisions();
}


