#ifndef GAME
#define GAME

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "GameField.h"
#include "menu.h"

class Game : public QObject
{
    Q_OBJECT
private:

    GameField *gameField;
    QGraphicsRectItem **field, **fieldNext;
    QGraphicsPixmapItem *logo;
    QGraphicsTextItem *score;

    QGraphicsRectItem *fieldBoard, *nextFigureBoard;
    QTimer *timer;

public:
    Button *butClose;
    QGraphicsScene *scene;
    Game();
    ~Game();
    bool eventFilter(QObject *, QEvent *);

    void Restart();

public slots:
    void Update();

signals:
    void EndGame(int);
};

#endif // GAME

