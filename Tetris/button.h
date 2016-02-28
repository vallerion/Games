#ifndef BUTTON
#define BUTTON

#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QObject>
#include <QMediaPlayer>
#include <QUrl>

class Button : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    QPixmap *state1, *state2;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

public:
    Button(const QPixmap& pixmap1, const QPixmap& pixmap2);
    ~Button();

signals:
    void clicked();
};
#endif // BUTTON

