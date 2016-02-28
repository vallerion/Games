#ifndef gameapp
#define gameapp

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include "game.h"
#include "menu.h"
#include "panel.h"

class GameApp : public QGraphicsView
{
    Q_OBJECT

    Game *game;
    Menu *menu;
    ResultScreen *screen;

public:
    GameApp(int width, int height, QWidget *parent = 0);
    ~GameApp();

    void ShowResultScreen();

public slots:
    void Play();
    void ShowMenu();

    void EndGame(int score);
};

#endif // GameApp

