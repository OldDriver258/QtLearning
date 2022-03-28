#include "booleanwindow.h"
#include "booleanmodel.h"
#include "booleanparser.h"
#include <QGridLayout>

BooleanWindow::BooleanWindow()
{
    label = new QLabel(tr("Boolean expression:"));
    lineEdit = new QLineEdit;

    booleanModel = new BooleanModel;

    treeView = new QTreeView;
    treeView->setModel(booleanModel);
    treeView->expandAll();

    connect(lineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(booleanExpressionChanged(QString)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(treeView, 1, 0, 1, 2);

    QWidget *w = new QWidget(this);
    w->setLayout(layout);
    setCentralWidget(w);

    setWindowTitle(tr("Boolean Parser"));
}

void BooleanWindow::booleanExpressionChanged(const QString &expr)
{
    BooleanParser parser;
    Node *rootNode = parser.parse(expr);
    booleanModel->setRootNode(rootNode);
    treeView->expandAll();
}
