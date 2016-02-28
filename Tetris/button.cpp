#include "button.h"



Button::Button(const QPixmap& pixmap1, const QPixmap& pixmap2)
{
    setAcceptHoverEvents(true);
    state1 = new QPixmap(pixmap1);
    state2 = new QPixmap(pixmap2);
    setPixmap(*state1);


}

Button::~Button()
{
    delete state1;
    delete state2;
    //delete hoverSound;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setPixmap(*state1);
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(*state2);
    //hoverSound->play();
    //qDebug() << hoverSound->errorString();
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(*state1);
}
