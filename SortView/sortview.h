#ifndef SORTVIEW_H
#define SORTVIEW_H

#include <QWidget>

class QListView;
class QStringListModel;
class QSortFilterProxyModel;
class QComboBox;

class SortView : public QWidget
{
    Q_OBJECT

public:
    SortView(QWidget *parent = 0);
    ~SortView();

private:
    QListView *view;
    QStringListModel *model;
    QSortFilterProxyModel *modelProxy;
    QComboBox *syntaxBox;

public Q_SLOTS:
    void filterChanged(const QString &text);
};
#endif // SORTVIEW_H
