#include "lightwidget.h"
#include "trafficlight.h"
QRectF LightWidget::boundingRect() const
{
    return QRectF(0,0,LightSize,LightSize);
}

LightWidget::LightWidget(const QColor &color, QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,m_color(color)
    ,m_on(false)
    ,m_IsClickable(true)
{
    setTransformOriginPoint(LightSize/2,LightSize/2);

}

void LightWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    setAcceptHoverEvents(true);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(m_color);
    painter->drawEllipse(0, 0, this->boundingRect().width(), this->boundingRect().height());
    if (!m_on){
        setOpacity(0.3);
    }else{
        setOpacity(1.0);
    }
    setScale(LightScale);

}

//void LightWidget::setGeometry(const QRectF &rect)
//{
//    prepareGeometryChange();
//    QGraphicsLayoutItem::setGeometry(rect);
//    qDebug()<<"Called";
//    setPos(rect.topLeft());
//}
//QSizeF LightWidget::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
//{
//    switch (which){
//    case Qt::MinimumSize:
//    case Qt::PreferredSize:
//        return this->boundingRect().size();
//    case Qt::MaximumSize:
//        return QSizeF(400,400);
//    default:
//        break;
//    }
//    return constraint;
//}

QColor LightWidget::getColor() const
{
    return m_color;
}
bool LightWidget::isOn() const
{
    return m_on;
}

void LightWidget::setOn(bool on)
{
    if (on == m_on)
        return;
    m_on = on;
    update(0,0,LightSize,LightSize);
}

void LightWidget::setColor(const QColor &color)
{
    m_color = color;
}

void LightWidget::TurnOnInteraction()
{
    setAcceptHoverEvents(true);
    m_IsClickable = true;
}

void LightWidget::TurnOffInteraction()
{
    setAcceptHoverEvents(false);
    m_IsClickable = false;
}

void LightWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //QGraphicsItem::mousePressEvent(event);
    Q_UNUSED(event);
    if(m_IsClickable){
        if(!m_on){
            this->turnOn();
            if(dynamic_cast<TrafficLight *>(this->parentItem())){
                QList<LightWidget *> *widget = (dynamic_cast<TrafficLight *>(this->parentItem()))->getLight();
                for(int i = 0 ; i < widget->size() ; i++){
                    if(widget->at(i) != this){
                        widget->at(i)->turnOff();
                    }
                }
            }
        }else{
            this->turnOff();
        }
    }
}

void LightWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::PointingHandCursor);
}

void LightWidget::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
     setCursor(QCursor(Qt::ArrowCursor));
}
//void LightWidget::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    setCursor(QCursor(Qt::PointingHandCursor));
//}

//void LightWidget::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
//{
//    setCursor(QCursor(Qt::PointingHandCursor));
//}

void LightWidget::turnOff()
{
    setOn(false);
}

void LightWidget::turnOn()
{
    setOn(true);
}
