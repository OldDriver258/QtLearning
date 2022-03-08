#ifndef CUSTONBUTTON_H
#define CUSTONBUTTON_H

#include <QPushButton>

class CustomButton : public QPushButton
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void onButtonClicked();
};

#endif // CUSTONBUTTON_H
