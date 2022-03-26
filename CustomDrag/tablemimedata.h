#ifndef TABLEMIMEDATA_H
#define TABLEMIMEDATA_H

#include "datatablewidget.h"
#include <QMimeData>
#include <QTableWidget>

class TableMimeData : public QMimeData
{
    Q_OBJECT
public:
    TableMimeData(const QTableWidget *tableWidget,
                  const QTableWidgetSelectionRange &range);

    const QTableWidget *tableWidget() const
    {
        return dataTableWidget;
    }
    QTableWidgetSelectionRange range() const
    {
        return selectionRange;
    }
    QStringList formats() const
    {
        return dataFormats;
    }

protected:
    QVariant retrieveData(const QString &format,
                          QVariant::Type preferredType) const;

private:
    QString toHtml(const QString &plainText) const;
    QString toCsv(const QString &plainText) const;
    QString selectionText() const;
//    QString text(int row, int column) const;


    const QTableWidget *dataTableWidget;
    QTableWidgetSelectionRange selectionRange;
    QStringList dataFormats;
};

#endif // TABLEMIMEDATA_H
