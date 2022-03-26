#include "datatablewidget.h"
#include <QTextDocument>
#include <QMouseEvent>
#include <QApplication>
#include <QAbstractItemView>
#include <QTableWidgetItem>
#if USE_QmimeData > 0
#include "tablemimedata.h"
#endif

DataTableWidget::DataTableWidget(QWidget *parent)
    : QTableWidget(parent)
{
    setAcceptDrops(true);                   // 开启拖拽功能
    setSelectionBehavior(SelectRows);       //一次选择一行
    setSelectionMode(ContiguousSelection);  //可以连续选择

    setColumnCount(3);
    setRowCount(5);
}

void DataTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }

    QTableWidget::mousePressEvent(event);
}

void DataTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }

//    QTableWidget::mouseMoveEvent(event);
}

void DataTableWidget::performDrag()
{
#if USE_QmimeData == 0
    QString selectedString = selectionText();
    if (selectedString.isEmpty())
        return;
#endif

#if USE_QmimeData > 0
    TableMimeData *mimeData = new TableMimeData(this, selectedRanges().at(0));
#else
    QMimeData *mimeData = new QMimeData;
    mimeData->setHtml(toHtml(selectedString));
    mimeData->setData("text/csv", toCsv(selectedString).toUtf8());
#endif

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
        selectionModel()->clearSelection();
    }
}

void DataTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DataTableWidget *source =
            qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }

//    QTableWidget::dragEnterEvent(event);
}

void DataTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DataTableWidget *source =
            qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }

//    QTableWidget::dragMoveEvent(event);
}

void DataTableWidget::dropEvent(QDropEvent *event)
{
#if USE_QmimeData > 0
    const TableMimeData *tableData =
            qobject_cast<const TableMimeData *>(event->mimeData());

    if (tableData) {
        /*
         * 通过  TableMimeData 可以拿到拖拽来源 QTableWidget 结构
         * 这里直接实现两个 QTableWidget 结构的拷贝即可
         */
        const QTableWidget *otherTable = tableData->tableWidget();
        QTableWidgetSelectionRange otherRange = tableData->range();

        for (int row = otherRange.topRow(); row <= otherRange.bottomRow(); row++) {
            for (int col = otherRange.leftColumn(); col <= otherRange.rightColumn(); col++) {
                if (row == otherRange.topRow()) {
                    setHorizontalHeaderItem(col - otherRange.leftColumn(),
                                            new QTableWidgetItem(*otherTable->horizontalHeaderItem(col)));
                }
                setItem(row - otherRange.topRow(), col - otherRange.leftColumn(),
                        new QTableWidgetItem(*otherTable->item(row, col)));
            }
        }
        event->acceptProposedAction();
    } else if (event->mimeData()->hasFormat("text/csv")) {
        QByteArray csvData = event->mimeData()->data("text/csv");
        QString csvText = QString::fromUtf8(csvData);
        fromCsv(csvText);
        event->acceptProposedAction();
    }
#else
    if (event->mimeData()->hasFormat("text/csv")) {
        QByteArray csvData = event->mimeData()->data("text/csv");
        QString csvText = QString::fromUtf8(csvData);
        fromCsv(csvText);
        event->acceptProposedAction();
    }
#endif
//    QTableWidget::dropEvent(event);
}

#if USE_QmimeData == 0
QString DataTableWidget::selectionText() const
{
    QString selectionString;
    QString headerString;
    QAbstractItemModel *itemModel = model();
    QTableWidgetSelectionRange selection = selectedRanges().at(0);

    for (int row = selection.topRow(), firstRow = row;
        row <= selection.bottomRow(); row++) {
        for (int col = selection.leftColumn();
             col <= selection.rightColumn(); col++) {
            if (row == firstRow) {
                headerString.append(horizontalHeaderItem(col)->text()).append("\t");
            }
            QModelIndex index = itemModel->index(row, col);
            selectionString.append(index.data().toString().append("\t"));
        }
        selectionString = selectionString.trimmed(); // 去掉头尾的空格
        selectionString.append("\n");
    }

    return headerString.trimmed() + "\n" + selectionString.trimmed();
}

QString DataTableWidget::toHtml(const QString &plainText) const
{
#if QT_VERSION >= 0x050000
    QString result = plainText.toHtmlEscaped();
#else
    QString result = Qt::escape(plainText);
#endif

    result.replace("\t", "<td>");
    result.replace("\n", "\n<tr><td>");
    result.prepend("<table>\n<tr><td>");
    result.append("\n</table>");

    return result;
}

QString DataTableWidget::toCsv(const QString &plainText) const
{
    QString result = plainText;
    result.replace("\\", "\\\\");
    result.replace("\"", "\\\"");
    result.replace("\t", "\", \"");
    result.replace("\n", "\"\n\"");
    result.prepend("\"");
    result.append("\"");
    return result;
}
#endif
void DataTableWidget::fromCsv(const QString &csvText)
{
    QStringList rows = csvText.split("\n");
    QStringList headers = rows.at(0).split(", ");

    for (int h = 0; h < headers.size(); ++h) {
        QString header = headers.at(h);
        headers.replace(h, header.replace('"', ""));
    }
    setHorizontalHeaderLabels(headers);

    for (int r = 1; r < rows.size(); ++r) {
        QStringList row = rows.at(r).split(", ");
        setItem(r - 1, 0, new QTableWidgetItem(row.at(0).trimmed().replace('"', "")));
        setItem(r - 1, 1, new QTableWidgetItem(row.at(1).trimmed().replace('"', "")));
        setItem(r - 1, 2, new QTableWidgetItem(row.at(2).trimmed().replace('"', "")));
    }
}

