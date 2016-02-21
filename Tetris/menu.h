#ifndef MENU
#define MENU

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QObject>

class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPixmap *state1, *state2;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
public:
    Button(QPixmap *pixmap1, QPixmap *pixmap2);
    ~Button();

signals:
    void clicked();
};

class Menu :public QObject
{
    Q_OBJECT
public:
    QGraphicsScene *scene;
    QGraphicsPixmapItem *logo;
    Button *butNewGame, *butHelp, *butExit, *butClassicMode, *butEndlessMode, *butOnlineMode,
           *butPMode;
    void ShowMenu();
    Menu();
    ~Menu();

private slots:
    void MoveBut();
};

#endif // MENU

