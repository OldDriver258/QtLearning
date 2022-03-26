#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QHeaderView>
#include <QStandardItemModel>

#define CREATE_TABLE    0
#define Oracle_Style    1
#define USE_TableModel  1
#define Rewrite_Record  1

bool connect(const QString &dbName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
    if (!db.open()) {
        QMessageBox::critical(0,
                              "Database Error",
                              db.lastError().text());
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if CREATE_TABLE > 0
    if (connect("demo.db")) {
        QSqlQuery query;
        if (!query.exec("CREATE TABLE student ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name VARCHAR,"
                        "age INT)")) {
            QMessageBox::critical(0,
                                  "Database Error",
                                  query.lastError().text());
            return 1;
        }
    } else {
        return 1;
    }
#endif
    if (connect("demo.db")) {
#if USE_TableModel == 0
        QSqlQuery query;

#if Oracle_Style == 0
        query.prepare("INSERT INTO student (name, age) VALUES (?, ?)");
        QVariantList names;
        names << "Tom" << "Jack" << "Jane" << "Jerry";
        query.addBindValue(names);
        QVariantList ages;
        ages << 20 << 23 << 22 << 25;
        query.addBindValue(ages);
#else
        query.prepare("INSERT INTO student (name, age) VALUES (:name, :age)");
        QVariantList names;
        names << "Tom" << "Jack" << "Jane" << "Jerry";
        query.bindValue(":name", names);
        QVariantList ages;
        ages << 20 << 23 << 22 << 25;
        query.bindValue(":age", ages);
#endif

        // 使用批处理的方式插入数据
        if (!query.execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query.lastError().text());
        }
        query.finish();
#else
        QSqlTableModel model;
        model.setTable("student");  // 选择 table

        int row = 0;
        model.insertRows(row, 1); // 在索引 0 的位置插入 1 行新的数据
        model.setData(model.index(row, 1), "Cheng");
        model.setData(model.index(row, 2), 24);  // 设置 name 和 age; id 数据库自动添加
        model.submitAll();
#endif

#if Rewrite_Record > 0
        model.setFilter("age == 25");
        if (model.select()) {
            if (model.rowCount() > 1) {
                QSqlRecord record = model.record(0);
                record.setValue("age", 99);
                model.setRecord(0, record);             // 两种设置记录的方法 setRecord
                model.setData(model.index(1, 2), 99);   // setData
                model.submitAll();
            }
        }
#endif

        // 查询数据
#if USE_TableModel == 0
        query.exec("SELECT name, age FROM student");
        while (query.next()) {
            QString name = query.value(0).toString();
            int age = query.value(1).toInt();
            qDebug() << name << ": " << age;
        }
#else
        model.setFilter("age > 20 and age < 25"); // 设置过滤相当于 WHERE age > 20 and age < 25
        if (model.select()) {   // 进行了查询操作
            for (int i = 0; i < model.rowCount(); i++) {
                QSqlRecord record = model.record(i);
                int id = record.value("id").toInt();
                QString name = record.value("name").toString();
                int age = record.value("age").toInt();
                qDebug() << id << ": " << name << ": " << age;
            }
        }
#endif

        model.setSort(1, Qt::AscendingOrder); // 升序
        model.setHeaderData(1, Qt::Horizontal, "Name");
        model.setHeaderData(2, Qt::Horizontal, "Age");
        model.select();

        QTableView *view = new QTableView;
        view->setModel(&model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->resizeColumnsToContents(); // 根据列内容调整大小
        view->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑

        QHeaderView *header = view->horizontalHeader();
        header->setStretchLastSection(true); // 该属性设置为true，以确保视图不会浪费任何为其头文件分配的空间

        view->show();
        a.exec();
    } else {
        return 1;
    }

    return a.exec();
}
