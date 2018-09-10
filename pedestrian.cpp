#include "pedestrian.h"

Pedestrian::Pedestrian(QGraphicsEllipseItem *parent):QGraphicsEllipseItem (parent)
{

}

QRectF Pedestrian::boundingRect() const
{
    return QRectF(0,0,15,15);
}

QPainterPath Pedestrian::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

Pedestrian::~Pedestrian()
{

}

void Pedestrian::advance(int phase)
{
    Q_UNUSED(phase)

}
