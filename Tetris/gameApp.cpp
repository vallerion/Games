#include "GameApp.h"

GameApp::GameApp(int width, int height, QWidget *parent)
{
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menu = new Menu();
    game = new Game();

    ShowMenu();

    connect(menu->butClassicMode,SIGNAL(clicked()),this,SLOT(playClassic()));
}

GameApp::~GameApp()
{
    delete game;
    delete menu;
}

void GameApp::playClassic()
{
    setScene(game->scene);
    this->installEventFilter(game);
    connect(game,SIGNAL(EndGame(int)),this,SLOT(EndGame(int)));
    connect(game->butClose,SIGNAL(clicked()),this,SLOT(ShowMenu()));
}

void GameApp::ShowMenu()
{
    setScene(menu->scene);
}

void GameApp::EndGame(int score)
{
    qDebug() << score;
}
