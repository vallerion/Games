#include "menu.h"

Menu::Menu()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,400,600);

    butNewGame = new Button(QPixmap(":/images/images/but_newGame_1.png"),QPixmap(":/images/images/but_newGame_2.png"));
    butNewGame->setPos(100,220);
    scene->addItem(butNewGame);

    butHelp = new Button(QPixmap(":/images/images/but_help_1.png"),QPixmap(":/images/images/but_help_2.png"));
    butHelp->setPos(100,270);
    scene->addItem(butHelp);

    butExit = new Button(QPixmap(":/images/images/but_exit_1.png"),QPixmap(":/images/images/but_exit_2.png"));
    butExit->setPos(100,320);
    scene->addItem(butExit);

    butClassicMode = new Button(QPixmap(":/images/images/but_classicmode_1.png"),QPixmap(":/images/images/but_classicmode_2.png"));
    butClassicMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 50);
    butClassicMode->setOpacity(0);
    scene->addItem(butClassicMode);

    butEndlessMode = new Button(QPixmap(":/images/images/but_endlessmode_1.png"),QPixmap(":/images/images/but_endlessmode_2.png"));
    butEndlessMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 90);
    butEndlessMode->setOpacity(0);
    scene->addItem(butEndlessMode);

    butOnlineMode = new Button(QPixmap(":/images/images/but_onlinemode_1.png"),QPixmap(":/images/images/but_onlinemode_2.png"));
    butOnlineMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 130);
    butOnlineMode->setOpacity(0);
    scene->addItem(butOnlineMode);

    logo = new QGraphicsPixmapItem();
    logo->setPixmap(QPixmap(":/images/images/tetrisPro_logo.png"));
    logo->setPos(120, 100);
    scene->addItem(logo);

    connect(butNewGame,SIGNAL(clicked()),this,SLOT(MoveBut()),Qt::UniqueConnection);
}

Menu::~Menu()
{
    delete scene;
    delete logo;
    delete butExit;
    delete butHelp;
    delete butNewGame;
    delete butClassicMode;
    delete butEndlessMode;
    delete butOnlineMode;
}

void Menu::MoveBut()
{
    if(butHelp->pos().y() == butNewGame->pos().y() + 50){
        butHelp->setPos(butHelp->pos().x(), butNewGame->pos().y() + 170);
        butExit->setPos(butExit->pos().x(), butNewGame->pos().y() + 220);

        butClassicMode->setOpacity(1);
        butEndlessMode->setOpacity(1);
        butOnlineMode->setOpacity(1);
    }
    else{
        butHelp->setPos(butHelp->pos().x(), butNewGame->pos().y() + 50);
        butExit->setPos(butExit->pos().x(), butNewGame->pos().y() + 100);

        butClassicMode->setOpacity(0);
        butEndlessMode->setOpacity(0);
        butOnlineMode->setOpacity(0);
    }
}
