#include "currencymodel.h"

CurrencyModel::CurrencyModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

// 纯虚函数, 返回行数
int CurrencyModel::rowCount(const QModelIndex &) const
{
    return currencyMap.count();
}

// 纯虚函数,返回列数
int CurrencyModel::columnCount(const QModelIndex &) const
{
    return currencyMap.count();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }
    return currencyAt(section);
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}

// 要重置内部数据
void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    beginResetModel();
    currencyMap = map;
    endResetModel();
}

// 纯虚函数, 填写 index 对应 role 中的数据
QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else if (role == Qt::DisplayRole || role == Qt::EditRole) { // Qt::EditRole 提供了一个编辑时的默认值
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());
        if (currencyMap.value(rowCurrency) == 0.0) {
            return "####";
        }
        double amount = currencyMap.value(columnCurrency) /
                        currencyMap.value(rowCurrency);
        return QString("%1").arg(amount, 0, 'f', 4);
    }

    return QVariant();
}

// 委托会通过 flags() 来检测数据是否可以编辑， 修改 flags() 标记那些 index 是可以修改的
Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if (index.row() != index.column()) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

/* index 原始数值的计算方法是 currencyMap["CNY"]/currencyMap["HKD"]
 * 用户修改的数值也是这个商的值， 这里分母是不变的， 分子的值需要修改
 * 分子新的值应当是 分母 * 输入数值
 */
bool CurrencyModel::setData (const QModelIndex &index,
                             const QVariant &value,
                             int role)
{
    if (index.isValid() &&
        index.row() != index.column() &&
        role == Qt::EditRole) {
        QString columnCurrency = headerData(index.column(),
                                            Qt::Horizontal,
                                            Qt::DisplayRole).toString();
        QString rowCurrency = headerData(index.row(),
                                         Qt::Vertical,
                                         Qt::DisplayRole).toString();
        currencyMap.insert(columnCurrency,
                           value.toDouble() * currencyMap.value(rowCurrency));
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

