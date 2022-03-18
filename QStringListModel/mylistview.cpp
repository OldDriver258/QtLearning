#include <QStringListModel>
#include <QListView>
#include <QBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QtDebug>
#include <QMessageBox>
#include "mylistview.h"

MyListView::MyListView(QWidget *parent)
    : QListView(parent)
{
    QStringList data;
    data << "Letter A" << "Letter B" << "Letter C";

    model = new QStringListModel(this);
    model->setStringList(data);

    listView = new QListView(this);
    listView->setModel(model);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    QPushButton *insertBtn = new QPushButton(tr("Insert"), this);

    connect(insertBtn, SIGNAL(clicked()),
            this,      SLOT(insertData()));

    QPushButton *delBtn = new QPushButton(tr("Delete"), this);

    connect(delBtn, SIGNAL(clicked()),
            this,   SLOT(deleteData()));

    QPushButton *showBtn = new QPushButton(tr("Show"), this);

    connect(showBtn, SIGNAL(clicked()),
            this,    SLOT(showData()));

    btnLayout->addWidget(insertBtn);
    btnLayout->addWidget(delBtn);
    btnLayout->addWidget(showBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(listView);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);
}

MyListView::~MyListView()
{
}

void MyListView::insertData()
{
    bool isOk;

    /*
     * 输入对话框
     * "Insert"                         对话框标题
     * "Please input a new data:"       展示应该输入什么数据
     * QLineEdit::Normal                是否显示输入的文字
     * "You are inserting a new data."  表示默认的输入内容
     * isOk                             用户是否按下 ok
     */
    QString text = QInputDialog::getText(this, "Insert",
                                         "Please input a new data:",
                                         QLineEdit::Normal,
                                         "You are inserting a new data.",
                                         &isOk);

    if (isOk) {
        int row = listView->currentIndex().row();
        model->insertRows(row, 1);          //插入空行

        QModelIndex index = model->index(row);
        model->setData(index, text);        //插入数据
        listView->setCurrentIndex(index);   //设置对应的 index
        listView->edit(index);              //编辑 index 对应的数据
    }
}

void MyListView::deleteData()
{
    if (model->rowCount() > 1) {
        model->removeRows(listView->currentIndex().row(), 1);
    }
}

void MyListView::showData()
{
    QStringList data = model->stringList();
    QString str;

    foreach (QString s, data) {
        str += s + "\n";
    }
    QMessageBox::information(this, "Data", str);
}
