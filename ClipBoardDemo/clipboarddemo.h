#ifndef CLIPBOARDDEMO_H
#define CLIPBOARDDEMO_H

#include <QWidget>

class ClipboardDemo : public QWidget
{
    Q_OBJECT

public:
    ClipboardDemo(QWidget *parent = 0);
    ~ClipboardDemo();

private Q_SLOTS:
    void setClipboardDemoContent();
    void getClipboardDemoContent();
};
#endif // CLIPBOARDDEMO_H
