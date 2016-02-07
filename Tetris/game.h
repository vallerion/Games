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

class Game : public QGraphicsView
{
    Q_OBJECT

private:
    const int winH, winW;
    int score;
    QGraphicsScene *mainScene;
    GameField *gameField;
    QGraphicsRectItem **field, *fieldBoard;
    QGraphicsPixmapItem *logo;
    QGraphicsTextItem *scoreText;

    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public:
    Game(int win_width, int win_height, QWidget *parent = 0);
    ~Game();

public slots:
    void Update();
};

#endif // GAME

