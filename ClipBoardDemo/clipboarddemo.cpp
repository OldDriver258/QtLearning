#include "clipboarddemo.h"
#include <QLayout>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QClipboard>
#include <QApplication>
#include <QMessageBox>

ClipboardDemo::ClipboardDemo(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *northLayout = new QHBoxLayout;
    QHBoxLayout *southLayout = new QHBoxLayout;

    QTextEdit *editor = new QTextEdit;
    QLabel *label = new QLabel;
    label->setText(tr("Text Input: "));
    label->setBuddy(editor);

    QPushButton *copyButton = new QPushButton;
    copyButton->setText("Set Clipboard");
    QPushButton *pasteButton = new QPushButton;
    pasteButton->setText("Get Clipboard");

    northLayout->addWidget(label);
    northLayout->addWidget(editor);
    southLayout->addWidget(copyButton);
    southLayout->addWidget(pasteButton);
    mainLayout->addLayout(northLayout);
    mainLayout->addLayout(southLayout);

    connect(copyButton, SIGNAL(clicked()),
            this,       SLOT(setClipboardDemoContent()));
    connect(pasteButton, SIGNAL(clicked()),
            this,       SLOT(getClipboardDemoContent()));
}

ClipboardDemo::~ClipboardDemo()
{
}

void ClipboardDemo::setClipboardDemoContent()
{
    QClipboard *board = QApplication::clipboard();
    // 通过setText()，setImage()或者setPixmap()函数可以将数据放置到剪贴板内
    board->setText("Text from Qt Application");
}

void ClipboardDemo::getClipboardDemoContent()
{
    QClipboard *board = QApplication::clipboard();
    // 使用text()，image()或者pixmap()函数则可以从剪贴板获得数据，也就是粘贴
    QString str = board->text();
    QMessageBox::information(NULL, "From clipboard", str);
}

