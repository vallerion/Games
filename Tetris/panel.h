#ifndef PANEL
#define PANEL

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QDebug>
#include <QObject>
#include <QList>

#include "button.h"

class ResultScreen : public QObject
{
    Q_OBJECT
    QGraphicsTextItem *result, *score;
    QGraphicsRectItem *bkg;

public:
    enum State{pause,gameOver};
    Button *butRestart, *butClose, *butRecord;

    QList<QGraphicsItem*> itemList;

    ResultScreen();
    ~ResultScreen();

    void Show(const int, const QString& text = "", State st = pause);
};

#endif // PANEL

