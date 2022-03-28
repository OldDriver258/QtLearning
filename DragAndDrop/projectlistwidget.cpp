#include "projectlistwidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>

ProjectListWidget::ProjectListWidget(QWidget *)
{
    setAcceptDrops(true);
}

void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();

    QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        // 计算鼠标按下时的位移量
        int distance = (event->pos() - startPos).manhattanLength();
        // 鼠标的拖动需要一个最小距离, 相当于消除抖动
        // QApplication::startDragDistance() 一般是 4px
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }

    QListWidget::mouseMoveEvent(event);
}

void ProjectListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();
    if (item) {
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);            // 拖拽中存储的数据
        drag->setPixmap(QPixmap(":/image/OpenFile.jpg"));   // 拖拽中鼠标的样式
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction)   // 阻塞等待拖拽动作完成
            delete item;
    }
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()) {
        event->acceptProposedAction();
    }
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ProjectListWidget *source =
            qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
    ProjectListWidget *source =
            qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}
