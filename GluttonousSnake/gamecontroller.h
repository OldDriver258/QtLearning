#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QAction>

class QGraphicsScene;
class QTimer;
class Snake;
class QKeyEvent;
class Food;
class QAction;

class GameController : public QObject
{
    Q_OBJECT

public:
    GameController(QGraphicsScene &scene, QObject *parent = 0);

    void snakeAteFood(Snake *snake, Food *food);
    void snakeAteItself(Snake *snake);

    QAction *getResmueAction(){ return resumeAction;}
    void setResumeAction(QAction* r){ resumeAction = r; }

public slots:
    void pause(void);
    void resume(void);
    void gameOver(void);

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();
    void setResume() {resumeAction->setEnabled(isPause);}

    QAction        *resumeAction;
    QTimer          timer;
    QGraphicsScene &scene;
    Snake          *snake;
    bool            isPause;
};

#endif // GAMECONTROLLER_H
