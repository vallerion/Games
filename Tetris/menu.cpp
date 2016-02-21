#include "menu.h"

void Menu::ShowMenu()
{
}

Menu::Menu()
{
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,400,600);

    butNewGame = new Button(new QPixmap(":/images/images/but_newGame_1.png"),new QPixmap(":/images/images/but_newGame_2.png"));
    butNewGame->setPos(100,220);
    scene->addItem(butNewGame);

    butHelp = new Button(new QPixmap(":/images/images/but_help_1.png"),new QPixmap(":/images/images/but_help_2.png"));
    butHelp->setPos(100,270);
    scene->addItem(butHelp);

    butExit = new Button(new QPixmap(":/images/images/but_exit_1.png"),new QPixmap(":/images/images/but_exit_2.png"));
    butExit->setPos(100,320);
    scene->addItem(butExit);

    butClassicMode = new Button(new QPixmap(":/images/images/but_classicmode_1.png"),new QPixmap(":/images/images/but_classicmode_2.png"));
    butClassicMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 50);
    butClassicMode->setOpacity(0);
    scene->addItem(butClassicMode);

    butEndlessMode = new Button(new QPixmap(":/images/images/but_endlessmode_1.png"),new QPixmap(":/images/images/but_endlessmode_2.png"));
    butEndlessMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 90);
    butEndlessMode->setOpacity(0);
    scene->addItem(butEndlessMode);

    butOnlineMode = new Button(new QPixmap(":/images/images/but_onlinemode_1.png"),new QPixmap(":/images/images/but_onlinemode_2.png"));
    butOnlineMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 130);
    butOnlineMode->setOpacity(0);
    scene->addItem(butOnlineMode);

    butPMode = new Button(new QPixmap(":/images/images/but_pm_1.png"),new QPixmap(":/images/images/but_pm_2.png"));
    butPMode->setPos(butNewGame->pos().x() + 25, butNewGame->pos().y() + 170);
    butPMode->setOpacity(0);
    scene->addItem(butPMode);

    logo = new QGraphicsPixmapItem();
    logo->setPixmap(QPixmap(":/images/images/tetrisPro_logo.png"));
    logo->setPos(120, 100);
    scene->addItem(logo);

    connect(butNewGame,SIGNAL(clicked()),this,SLOT(MoveBut()));
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
    delete butPMode;
}

void Menu::MoveBut()
{
    if(butHelp->pos().y() == butNewGame->pos().y() + 50){
        butHelp->setPos(butHelp->pos().x(), butNewGame->pos().y() + 210);
        butExit->setPos(butExit->pos().x(), butNewGame->pos().y() + 260);

        butClassicMode->setOpacity(1);
        butEndlessMode->setOpacity(1);
        butOnlineMode->setOpacity(1);
        butPMode->setOpacity(1);
    }
    else{
        butHelp->setPos(butHelp->pos().x(), butNewGame->pos().y() + 50);
        butExit->setPos(butExit->pos().x(), butNewGame->pos().y() + 100);

        butClassicMode->setOpacity(0);
        butEndlessMode->setOpacity(0);
        butOnlineMode->setOpacity(0);
        butPMode->setOpacity(0);
    }
}





// button
Button::Button(QPixmap* pixmap1, QPixmap* pixmap2)
{
    setAcceptHoverEvents(true);
    state1 = pixmap1;
    state2 = pixmap2;
    setPixmap(*state1);
}

Button::~Button()
{
    delete state1;
    delete state2;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(*state2);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setPixmap(*state1);
}


