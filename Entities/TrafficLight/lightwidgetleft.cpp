#include "lightwidgetleft.h"

LightWidgetLeft::LightWidgetLeft(const QColor &color, QGraphicsItem *parent)
    :LightWidget(color,parent)
{
    setAcceptHoverEvents(true);
    setTransformOriginPoint(LightSize/2,LightSize/2);
}

void LightWidgetLeft::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    static const QPointF points[3] = {QPointF(0,this->boundingRect().height()/2),QPointF(this->boundingRect().width(),0),QPointF(this->boundingRect().width(),this->boundingRect().height())};
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(Qt::NoPen);
    painter->setBrush(getColor());
    painter->drawPolygon(points,3,Qt::OddEvenFill);
    painter->scale(0.8,0.8);
    if (!isOn()){
        setOpacity(0.3);
    }else{
        setOpacity(1.0);
    }
    setScale(LightScale);
}
