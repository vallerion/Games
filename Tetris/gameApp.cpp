#include "GameApp.h"

GameApp::GameApp(int width, int height, QWidget *parent)
{
    setFixedSize(width, height);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    menu = new Menu();
    game = new Game();
    screen = new ResultScreen();

    ShowMenu();

    connect(menu->butClassicMode,SIGNAL(clicked()),this,SLOT(Play()));
    connect(menu->butEndlessMode,SIGNAL(clicked()),this,SLOT(Play()));
    connect(menu->butExit,SIGNAL(clicked()),this,SLOT(close()));

    connect(game,SIGNAL(EndGame(int)),this,SLOT(EndGame(int)));
    connect(game->butClose,SIGNAL(clicked()),this,SLOT(ShowMenu()));

    connect(screen->butRestart,SIGNAL(clicked()),this,SLOT(Play()));
    connect(screen->butClose,SIGNAL(clicked()),this,SLOT(ShowMenu()));
}

GameApp::~GameApp()
{
    delete game;
    delete menu;
    delete screen;
}

void GameApp::Play()
{
    Button* but = qobject_cast<Button*>(sender());
    if(but == menu->butClassicMode)
        game->SetMode(Game::classic);
    else if(but == menu->butEndlessMode)
        game->SetMode(Game::endless);
    else if(but == menu->butOnlineMode)
        game->SetMode(Game::online);

    if(scene() == game->scene)
        for(auto it = screen->itemList.begin(); it != screen->itemList.end(); ++it)
            game->scene->removeItem(*it);

    game->Restart();
    setScene(game->scene);
    this->installEventFilter(game);
}

void GameApp::ShowMenu()
{
    game->Stop();
    setScene(menu->scene);
}

void GameApp::EndGame(int score)
{
    screen->Show(score,"YOU WIN!",ResultScreen::gameOver);

    for(auto it = screen->itemList.begin(); it != screen->itemList.end(); ++it)
        game->scene->addItem(*it);
}
