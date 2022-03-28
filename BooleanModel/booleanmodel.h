#ifndef BOOLEANMODEL_H
#define BOOLEANMODEL_H

#include <QAbstractItemModel>
#include "node.h"

class BooleanModel : public QAbstractItemModel
{
public:
    BooleanModel(QObject *parent = 0);
    ~BooleanModel();

    void setRootNode(Node *node);
    Node *nodeFromIndex(const QModelIndex &index) const;
    //实现五个虚函数
    QModelIndex index(int row, int column,
                          const QModelIndex &parent) const;
    QModelIndex parent( const QModelIndex & index ) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount( const QModelIndex & parent = QModelIndex() ) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    QVariant data(const QModelIndex & index,int role = Qt::DisplayRole) const;
private:
    Node *rootNode;
};

#endif // BOOLEANMODEL_H
