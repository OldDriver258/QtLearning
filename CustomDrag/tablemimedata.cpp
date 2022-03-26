#include "tablemimedata.h"
#include <QTextDocument>

TableMimeData::TableMimeData(const QTableWidget *tableWidget,
                             const QTableWidgetSelectionRange &range)
{
    dataTableWidget = tableWidget;
    selectionRange = range;
    dataFormats << "text/csv" << "text/html";


}

// 重载了数据类型转换的接口
QVariant TableMimeData::retrieveData(const QString &format,
                                     QVariant::Type preferredType) const
{
    if (format == "text/csv") {
        return toCsv(selectionText());
    } else if (format == "text/html") {
        return toHtml(selectionText());
    } else {
        return QMimeData::retrieveData(format, preferredType);
    }
}

QString TableMimeData::selectionText() const
{
    QString selectionString;
    QString headerString;
    QAbstractItemModel *itemModel = tableWidget()->model();
    QTableWidgetSelectionRange selection = range();

    for (int row = selection.topRow(), firstRow = row;
        row <= selection.bottomRow(); row++) {
        for (int col = selection.leftColumn();
             col <= selection.rightColumn(); col++) {
            if (row == firstRow) {
                headerString.append(tableWidget()->horizontalHeaderItem(col)->text()).append("\t");
            }
            QModelIndex index = itemModel->index(row, col);
            selectionString.append(index.data().toString().append("\t"));
        }
        selectionString = selectionString.trimmed(); // 去掉头尾的空格
        selectionString.append("\n");
    }

    return headerString.trimmed() + "\n" + selectionString.trimmed();
}

QString TableMimeData::toHtml(const QString &plainText) const
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

QString TableMimeData::toCsv(const QString &plainText) const
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


