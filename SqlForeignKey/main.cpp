#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QTableView>
#include <QHeaderView>
#include <QSqlRelationalTableModel>

#define CREATE_TABLE    1

enum ColumnIndex
{
    Column_ID = 0,
    Column_Name = 1,
    Column_Age = 2,
    Column_City = 3
};

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

    if (connect("demo.db")) {
#if CREATE_TABLE > 0
        QSqlQuery query;

        query.exec("DROP TABLE city");
        query.exec("DROP TABLE student");

        if (!query.exec("CREATE TABLE city ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name VARCHAR)")) {
            QMessageBox::critical(0,
                                  "Database Error",
                                  query.lastError().text());
            return 1;
        }

        if (!query.exec("CREATE TABLE student ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                        "name VARCHAR,"
                        "age INTEGER,"
                        "address INTEGER,"
                        "FOREIGN KEY(address) REFERENCES city(id));")) {
            QMessageBox::critical(0,
                                  "Database Error",
                                  query.lastError().text());
            return 1;
        }

        /*
         * 插入 city 中的数据
         */
        query.prepare("INSERT INTO city (name) VALUES (:name)");
        QVariantList cityNames;
        cityNames << "Beijing" << "Shanghai" << "Nanjing" << "Tianjin"
                  << "Wuhan" << "Hangzhou" << "Suzhou" << "Guangzhou";
        query.bindValue(":name", cityNames);

        // 使用批处理的方式插入数据
        if (!query.execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query.lastError().text());
        }
        query.finish();

        /*
         * 插入 student 中的数据
         */
        query.prepare("INSERT INTO student (name, age, address) "
                      "VALUES (:name, :age, :address)");
        QVariantList studentNames;
        studentNames << "Tom" << "Jack" << "Jane" << "Jerry";
        query.bindValue(":name", studentNames);
        QVariantList studentAge;
        studentAge << 20 << 23 << 22 << 25;
        query.bindValue(":age", studentAge);
        QVariantList studentAddress;
        studentAddress << 2 << 1 << 4 << 5;
        query.bindValue(":address", studentAddress);

        // 使用批处理的方式插入数据
        if (!query.execBatch()) {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  query.lastError().text());
        }
        query.finish();
#endif

        QSqlRelationalTableModel *model = new QSqlRelationalTableModel;
        model->setTable("student");
        model->setSort(Column_Name, Qt::AscendingOrder);
        model->setHeaderData(Column_Name, Qt::Horizontal, "Name");
        model->setHeaderData(Column_Age, Qt::Horizontal, "Age");
        model->setHeaderData(Column_City, Qt::Horizontal, "City");
        // Column_City 列中的值会对应 city 中的 id, 最终输出 city 中的 name
        model->setRelation(Column_City, QSqlRelation("city", "id", "name")); // 设置数据库外键
        model->select();

        QTableView *view = new QTableView;
        view->setModel(model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setColumnHidden(Column_ID, true);
        view->resizeColumnsToContents();
        view->resizeRowsToContents();

        QHeaderView *header = view->horizontalHeader();
        header->setStretchLastSection(true);

        view->show();
        a.exec();
    } else {
        return 1;
    }

    return a.exec();
}
