#include "shape.h"

Shapes::Shapes(FIGURE s, Pos pos) :
    _shape(s),
    p(pos)
{

    this->setPos(p.getX(),p.getY());
}



QRectF Shapes::boundingRect() const
{
    return QRectF(0,0,0,0);
}

void Shapes::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));

    switch (_shape) {
    case FIGURE::CROSS:
        painter->drawLine(QLineF(-p.width() / 10, p.height() / 10, p.width() / 10, -p.height() / 10)); // ширина фигуры = ширина представления деленная на 10;
        painter->drawLine(QLineF(p.width() / 10, p.height() / 10, -p.width() / 10, -p.height() / 10));
        break;
    case FIGURE::CIRCLE:
        painter->drawEllipse(QRectF(-p.width() / 10, -p.height() / 10, p.width() / 5, p.height() / 5));
        break;
    default:;
        qDebug() << "ERROR: " << ERRORS::SHAPE_NOT_DEFINED;
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}


Pos::Pos(const int &rect_w, const int &rect_h, const SECTIONS s) :
    w(rect_w),
    h(rect_h),
    _s(s)
{

    section();
}

int Pos::getX()
{
    switch (col) {
    case COLUMN::FIRST_COLUMN:
        return w / 6;
    case TWO_COLUMN:
        return w / 2;
    case THREE_COLUMN:
        return w/ 1.2 ;
    default:
        qDebug() << "Функция getX завершилась с кодом: " << UNDEFINED_COLUMN;
        return UNDEFINED_COLUMN;
    }
}

int Pos::getY()
{
    switch (row) {
    case ROWS::FIRST_ROW:
        return h / 6;
    case TWO_ROW:
        return h / 2;
    case THREE_ROW:
        return h / 1.2 ;
    default:
        qDebug() << "Функция getY завершилась с кодом: " << UNDEFINED_ROW;
        return UNDEFINED_ROW;
    }
}

int &Pos::width()
{
    return w;
}

int &Pos::height()
{
    return h;
}

int Pos::section()
{
    if(_s == SECTIONS::UNDEFINED) return 0;

    switch (_s) {
    case SECTIONS::FIRST:
        row = FIRST_ROW, col = FIRST_COLUMN;
        return ERRORS::NO;
    case SECOND:
        row = FIRST_ROW, col = TWO_COLUMN;
        return ERRORS::NO;
    case THIRD:
        row = FIRST_ROW, col = THREE_COLUMN;
        return ERRORS::NO;
    case FOURTH:
        row = TWO_ROW, col = FIRST_COLUMN;
        return ERRORS::NO;
    case FIFTH:
        row = TWO_ROW, col = TWO_COLUMN;
        return ERRORS::NO;
    case SIXTH:
        row = TWO_ROW, col = THREE_COLUMN;
        return ERRORS::NO;
    case SEVENTH:
        row = THREE_ROW, col = FIRST_COLUMN;
        return ERRORS::NO;
    case EIGHTH:
        row = THREE_ROW, col = TWO_COLUMN;
        return ERRORS::NO;
    case NINTH:
        row = THREE_ROW, col = THREE_COLUMN;
        return ERRORS::NO;
    default:
        qDebug() << "ERROR:" << ERRORS::ROW_AND_COLUMN_DEFINED_INCORRECTLY;
    }
    return ERRORS::ROW_AND_COLUMN_DEFINED_INCORRECTLY;
}
