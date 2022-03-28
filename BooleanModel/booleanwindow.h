#ifndef BOOLEANWINDOW_H
#define BOOLEANWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QTreeView>
#include "booleanmodel.h"

class BooleanWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit BooleanWindow();

public Q_SLOTS:
    void booleanExpressionChanged(const QString &expr);

private:
    QLabel         *label;
    QLineEdit      *lineEdit;

    BooleanModel   *booleanModel;
    QTreeView      *treeView;
};

#endif // BOOLEANWINDOW_H
