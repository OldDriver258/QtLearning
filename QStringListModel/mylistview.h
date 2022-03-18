#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QListView>

class QStringListModel;

class MyListView : public QListView
{
    Q_OBJECT

public:
    MyListView(QWidget *parent = 0);
    ~MyListView();

public slots:
    void insertData();
    void deleteData();
    void showData();

private:
    QStringListModel *model;
    QListView *listView;
};

#endif // MYLISTVIEW_H
