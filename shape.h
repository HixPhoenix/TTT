#ifndef SHAPE_H
#define SHAPE_H

#include "setting.h"
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPainter>

class Pos
{
public:
    Pos(const int &rect_w,const int &rect_h, const SECTIONS s);
    int getX();
    int getY();
    int& width();
    int& height();
private:
    int w,h;
    ROWS row{ROWS::UNDEFINED_ROW};
    COLUMN col{COLUMN::UNDEFINED_COLUMN};
    SECTIONS _s{SECTIONS::UNDEFINED};


    int section();
};

class Shapes : public QObject, public QGraphicsItem
{
Q_OBJECT
public:
    Shapes(FIGURE s, Pos pos);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    FIGURE _shape;
    Pos p;
};

#endif // SHAPE_H
