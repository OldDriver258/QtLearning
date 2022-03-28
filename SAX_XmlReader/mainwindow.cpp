#include "mainwindow.h"
#include <QMessageBox>

enum colName{
    colTree = 0,
    colPages
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("SAX XML Reader"));

    treeWidget = new QTreeWidget(this);
    QStringList headers;
    headers << "Items" << "Pages";
    treeWidget->setHeaderLabels(headers);
    setCentralWidget(treeWidget);
}

MainWindow::~MainWindow()
{
}

bool MainWindow::readFile(const QString &fileName)
{
    currentItem = 0;

    QFile file(fileName);
    QXmlInputSource inputSource(&file);
    QXmlSimpleReader reader;

    reader.setContentHandler(this);
    reader.setErrorHandler(this);

    return reader.parse(inputSource);
}

/*
 * startElement() 在读取到一个新的开始标签时被调用
 */
bool MainWindow::startElement(const QString &,
                              const QString &,
                              const QString &qName,
                              const QXmlAttributes &attributes)
{
    if (qName == "entry") {
        currentItem = new QTreeWidgetItem(currentItem ?
                                          currentItem : treeWidget->invisibleRootItem());
        currentItem->setText(0, attributes.value("term"));
    } else if (qName == "page") {
        currentText.clear();
    }

    return true;
}

/*
 * characters() 在读到字符数据的时候会调用
 */
bool MainWindow::characters(const QString &str)
{
    currentText += str;
    return true;
}

/*
 * endElement() 在遇到一个结束标签时被调用
 */
bool MainWindow::endElement(const QString &,
                            const QString &,
                            const QString &qName)
{
    if (qName == "entry") {
        currentItem = currentItem->parent();
    } else if (qName == "page") {
        if (currentItem) {
            QString allPages = currentItem->text(colPages);
            if (!allPages.isEmpty())
                allPages += ", ";
            allPages += currentText;
            currentItem->setText(colPages, allPages);
        }
    }

    return true;
}

bool MainWindow::fatalError(const QXmlParseException &exception)
{
    QMessageBox::critical(this,
                          tr("SAX Error"),
                          tr("Parse error at line %1, column %2:\n %3")
                          .arg(exception.lineNumber())
                          .arg(exception.columnNumber())
                          .arg(exception.message()));
    return false;
}
