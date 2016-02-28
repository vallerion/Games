#include "panel.h"

ResultScreen::ResultScreen()
{
    result = new QGraphicsTextItem();
    result->setFont(QFont("Arial Black",20,-1,true));
    result->setDefaultTextColor(QColor::fromRgb(180,0,0));

    score = new QGraphicsTextItem();
    score->setFont(QFont("Arial Black",16,-1,true));
    score->setDefaultTextColor(QColor::fromRgb(180,0,0));

    butRestart = new Button(QPixmap(":/images/images/but_restart_1.png"),QPixmap(":/images/images/but_restart_2.png"));
    butRestart->setPos(250, 500);

    butRecord = new Button(QPixmap(":/images/images/but_record_1.png"),QPixmap(":/images/images/but_record_2.png"));
    butRecord->setPos(165, 170);

    butClose = new Button(QPixmap(":/images/images/but_back2_1 .png"),QPixmap(":/images/images/but_back2_2 .png"));
    butClose->setPos(150, 500);

    bkg = new QGraphicsRectItem();
    bkg->setPen(QPen(QBrush(QColor::fromRgb(0,0,0)),0,Qt::NoPen, Qt::SquareCap, Qt::MiterJoin));
    bkg->setBrush(QBrush(QColor::fromRgb(255,255,255)));
    bkg->setOpacity(0.9);
    bkg->setRect(0,70,400,530);

    itemList.push_back(bkg);
    itemList.push_back(butClose);
    itemList.push_back(butRecord);
    itemList.push_back(butRestart);
    itemList.push_back(score);
    itemList.push_back(result);
}



ResultScreen::~ResultScreen()
{
    delete result;
    delete score;
    delete bkg;

    delete butRecord;
    delete butRestart;
    delete butClose;
}

void ResultScreen::Show(const int scr, const QString &text, ResultScreen::State st)
{
    score->setHtml(QString("Score: ")+ QString::number(scr));
    score->setPos(200 - score->boundingRect().width()/2, 260);
    result->setHtml(text);
    result->setPos(200 - result->boundingRect().width()/2, 80);
    butRecord->setVisible(st);
}

