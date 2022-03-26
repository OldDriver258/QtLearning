#include <QApplication>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>
#include <QSqlTableModel>
#include <QSqlRecord>

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
        QSqlTableModel model;
        model.setTable("setTable");
        model.setFilter("age > 20 and age < 25");
        if (model.select()) {
            for (int i = 0; i < model.rowCount(); i++) {
                QSqlRecord record = model.record(i);
                QString name = record.value("name").toString();
                int age = record.value("age").toInt();
                qDebug() << name << ": " << age;
            }
        }
    }

    return a.exec();
}
