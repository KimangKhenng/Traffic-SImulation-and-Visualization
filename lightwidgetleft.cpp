#include "lightwidgetleft.h"
#
LightWidgetLeft::LightWidgetLeft(const QColor &color, LightWidget *parent):LightWidget(color,parent)
{

}

void LightWidgetLeft::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static const QPointF points[3] = {QPointF(0,this->boundingRect().height()/2),QPointF(this->boundingRect().width(),0),QPointF(this->boundingRect().width(),this->boundingRect().height())};
    painter->setRenderHint(QPainter::Antialiasing);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (!isOn()){
//        painter->setBrush(Qt::red);
//        painter->drawPolygon(points,3,Qt::OddEvenFill);
        return;
    }
    painter->setBrush(getColor());
    painter->drawPolygon(points,3,Qt::OddEvenFill);
}
