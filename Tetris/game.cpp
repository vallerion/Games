#include "game.h"

Game::Game(int win_width, int win_height, QWidget *parent)
    : winH(win_height), winW(win_width)
{
    mainScene = new QGraphicsScene();   
    mainScene->setSceneRect(0, 0, winW, winH);
    setScene(mainScene);
//    showFullScreen();
//    mainScene->setSceneRect(rect());
    setFixedSize(winW, winH);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    logo = new QGraphicsPixmapItem();
    logo->setPixmap(QPixmap(":/images/tetrisPro_logo.png"));
    logo->setPos(160, 10);
    mainScene->addItem(logo);
    // create field
    gameField = new GameField(10, 20);
    gameField->CreateFigure();

    // create graphic field
    field = new QGraphicsRectItem*[gameField->height];
    for(int i = 0; i < gameField->height; i++)
        field[i] = new QGraphicsRectItem[gameField->width];

    for(int i = 0; i < gameField->height; i++)
        for(int j = 0; j < gameField->width; j++){
            field[i][j].setRect(j * 26 + 15, i * 26 + 71, 26, 26);
            field[i][j].setPen(QPen(QBrush(QColor::fromRgb(0,0,0)),2,Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
            field[i][j].setBrush(QBrush(QColor::fromRgb(255,0,0)));
            field[i][j].setVisible(gameField->gameFieldArray[i][j]);
            mainScene->addItem(&field[i][j]);
        }

    fieldBoard = new QGraphicsRectItem(14, 70, 260, 520);
    mainScene->addItem(fieldBoard);

    score = 0;
    scoreText = new QGraphicsTextItem(QString("Score: " + QString::number(score)));
    scoreText->setPos(280, 80);
    mainScene->addItem(scoreText);


    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(Update()));

    timer->start(50);    

    show();
}

Game::~Game()
{
    delete mainScene;
    delete gameField;
    delete fieldBoard;
}

void Game::mousePressEvent(QMouseEvent *event)
{
//    if(event->pos().y() < winH / 2)
//        field->MoveRotateFigure();
//    if(event->pos().x() > winW / 2 && event->pos().y() > winH / 2)
//        field->MoveRightFigure();
//    else if(event->pos().x() < winW / 2 && event->pos().y() > winH / 2)
//        field->MoveLeftFigure();
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
}

void Game::keyPressEvent(QKeyEvent *event)
{
    scoreText->setHtml(QString("Score: " + QString::number(++score)));
    if(event->key() == Qt::Key_Up)
        gameField->MoveRotateFigure();
    if(event->key() == Qt::Key_Right)
        gameField->MoveRightFigure();
    if(event->key() == Qt::Key_Left)
        gameField->MoveLeftFigure();
    if(event->key() == Qt::Key_Down)
        gameField->SpeedUpFigure();
}

void Game::Update()
{
    if(gameField->CheckCollisionDown())
        gameField->MoveDownFigure();
    else
    {
        gameField->CheckLine();
        gameField->CreateFigure();
    }

    for(int i = 0; i < gameField->height; i++)
        for(int j = 0; j < gameField->width; j++)
            field[i][j].setVisible(gameField->gameFieldArray[i][j]);
}
