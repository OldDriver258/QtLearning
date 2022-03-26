#ifndef DATATABLEWIDGET_H
#define DATATABLEWIDGET_H

#include <QTableWidget>

#define USE_QmimeData   true

class DataTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    DataTableWidget(QWidget *parent = 0);

protected:
    // 实现自定义拖拽需要实现的事件
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void performDrag();

#if USE_QmimeData == 0
    QString selectionText() const;
    QString toHtml(const QString &plainText) const;
    QString toCsv(const QString &plainText) const;
#endif
    void fromCsv(const QString &csvText);


    QPoint startPos;
};

#endif // DATATABLEWIDGET_H
