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

public:
    enum Mode{classic,endless,online};

    Button *butClose;
    QGraphicsScene *scene;

    Game();
    ~Game();

    bool eventFilter(QObject *, QEvent *);

    void Restart();
    void Stop();
    void SetMode(Mode);

public slots:
    void Update();

signals:
    void EndGame(int);

private:

    QMediaPlayer *bkgSound, *fallSound;

    GameField *gameField;
    QGraphicsRectItem **field, **fieldNext;
    QGraphicsPixmapItem *logo;
    QGraphicsTextItem *score;

    QGraphicsRectItem *fieldBoard, *nextFigureBoard;
    QTimer *timer;
    Mode mode;
};

#endif // GAME

