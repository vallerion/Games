#include "game.h"

Game::Game()
{
    scene = new QGraphicsScene();
    butClose = new Button(new QPixmap(":/images/images/but_back_1.png"),new QPixmap(":/images/images/but_back_2.png"));
    butClose->setPos(360,13);
    scene->addItem(butClose);

    // create logo, game field and next figure field
    logo = new QGraphicsPixmapItem();
    logo->setPixmap(QPixmap(":/images/images/tetrisPro_logo.png"));
    logo->setPos(130, 10);
    scene->addItem(logo);

    // create field
    gameField = new GameField(10, 20);


    fieldBoard = new QGraphicsRectItem(14, 70, 260, 520);
    scene->addItem(fieldBoard);

    nextFigureBoard = new QGraphicsRectItem(274, 70, 104, 104);
    scene->addItem(nextFigureBoard);

    score = new QGraphicsTextItem(QString("Score: " + QString::number(gameField->GetScore())));
    score->setPos(280, 300);
    scene->addItem(score);

    fieldNext = new QGraphicsRectItem*[4];
    for(int i = 0; i < 4; i++)
        fieldNext[i] = new QGraphicsRectItem[4];

    field = new QGraphicsRectItem*[gameField->height];
    for(int i = 0; i < gameField->height; i++)
        field[i] = new QGraphicsRectItem[gameField->width];

    for(int i = 0; i < gameField->height; i++)
        for(int j = 0; j < gameField->width; j++){
            if(i < 4 && j < 4){
                fieldNext[i][j].setRect(j * 26 + 275, i * 26 + 71, 26, 26);
                fieldNext[i][j].setPen(QPen(QBrush(QColor::fromRgb(0,0,0)),2,Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
                fieldNext[i][j].setBrush(QBrush(QColor::fromRgb(255,0,0)));
                fieldNext[i][j].setVisible(gameField->NextFigure()[i][j]);
                scene->addItem(&fieldNext[i][j]);
            }
            field[i][j].setRect(j * 26 + 15, i * 26 + 71, 26, 26);
            field[i][j].setPen(QPen(QBrush(QColor::fromRgb(0,0,0)),2,Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            field[i][j].setBrush(QBrush(QColor::fromRgb(255,0,0)));
            field[i][j].setVisible(gameField->gameFieldArray[i][j]);
            scene->addItem(&field[i][j]);
        }

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(Update()));
    timer->start(50);
}

Game::~Game()
{
    delete butClose;
    delete fieldBoard;
    delete nextFigureBoard;
    delete score;

    for(int i = 0; i < gameField->height; i++){
        delete[]field[i];
        if(i < 4)
            delete[]fieldNext[i];
    }
    delete[]field;
    delete[]fieldNext;

    delete gameField;
    delete logo;
    delete scene;
}

bool Game::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        switch(keyEvent->key()){
            case Qt::Key_Up:
                gameField->MoveRotateFigure();
                return true;
            case Qt::Key_Right:
                gameField->MoveRightFigure();
                return true;
            case Qt::Key_Left:
                gameField->MoveLeftFigure();
                return true;
            case Qt::Key_Down:
                gameField->SpeedUpFigure();
                return true;
        }
    }
    return QObject::eventFilter(obj,event);
}

void Game::Restart()
{
    gameField->CreateFigure();
}

void Game::Update()
{
    if(gameField->CheckCollisionDown())
        gameField->MoveDownFigure();
    else
    {
        gameField->CheckLine();
        if(gameField->CheckGameOver()){
            emit EndGame(gameField->GetScore());
            timer->stop();
        }
        score->setHtml(QString("Score: " + QString::number(gameField->GetScore())));
        gameField->CreateFigure();
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                fieldNext[i][j].setVisible(gameField->NextFigure()[i][j]);
    }

    for(int i = 0; i < gameField->height; i++)
        for(int j = 0; j < gameField->width; j++)
            field[i][j].setVisible(gameField->gameFieldArray[i][j]);
}
