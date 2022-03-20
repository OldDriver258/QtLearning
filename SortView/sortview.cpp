#include <QStringListModel>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QBoxLayout>
#include <QRegExp>
#include "sortview.h"

SortView::SortView(QWidget *parent)
    : QWidget(parent)
{
    // QColor::colorNames() 提供了一个 StringList
    model = new QStringListModel(QColor::colorNames(), this);

    // 设置了一个代理model, 且对第一列进行过滤
    modelProxy = new QSortFilterProxyModel(this);
    modelProxy->setSourceModel(model);
    modelProxy->setFilterKeyColumn(0);

    view = new QListView(this);
    view->setModel(modelProxy);

    // filter Part
    QLineEdit *filterInput = new QLineEdit;
    QLabel *filterLabel = new QLabel(tr("Filter"));

    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterLabel);
    filterLayout->addWidget(filterInput);

    // Syntax Part
    syntaxBox = new QComboBox;
    syntaxBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    syntaxBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxBox->addItem(tr("Fixed string"), QRegExp::FixedString);

    QLabel *syntaxLabel = new QLabel(tr("Syntax"));

    QHBoxLayout *syntaxLayout = new QHBoxLayout;
    syntaxLayout->addWidget(syntaxLabel);
    syntaxLayout->addWidget(syntaxBox);

    // whole window
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(view);
    layout->addLayout(filterLayout);
    layout->addLayout(syntaxLayout);

    connect(filterInput, SIGNAL(textChanged(QString)),
            this,        SLOT(filterChanged(QString)));
}

SortView::~SortView()
{
}

void SortView::filterChanged(const QString &text)
{
    // 从 syntaxBox 获取正则表达式的规则
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(
                syntaxBox->itemData(syntaxBox->currentIndex()).toInt());
    // 将 text 输入和正则表达式规则查看结果
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    // 过滤剩下的内容
    modelProxy->setFilterRegExp(regExp);
}

