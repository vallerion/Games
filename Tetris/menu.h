#ifndef MENU
#define MENU

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>
#include <QObject>

#include "button.h"

class Menu :public QObject
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *logo;
    Button *butNewGame, *butHelp, *butExit, *butClassicMode, *butEndlessMode, *butOnlineMode;
    Menu();
    ~Menu();

private slots:
    void MoveBut();
};

#endif // MENU

