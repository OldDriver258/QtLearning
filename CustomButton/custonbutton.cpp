#include "custonbutton.h"
#include <QDebug>
#include <QMouseEvent>

CustomButton::CustomButton(QWidget *parent)
    : QPushButton(parent)
{
    connect(this, SIGNAL(clicked(bool)),
            this, SLOT(onButtonClicked()));
}

void CustomButton::onButtonClicked()
{
    qDebug() << "You click this!";
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        qDebug() << "left";
    } else {
        QPushButton::mousePressEvent(event);
    }
}

