#include "lightwidget.h"

QRectF LightWidget::boundingRect() const
{
    return QRectF(0,0,SIZE,SIZE);
}

LightWidget::LightWidget(const QColor &color, QGraphicsItem *parent):QGraphicsItem(parent),m_color(color),m_on(false)
{

}

void LightWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if (!m_on)
        return;
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(m_color);
    painter->drawEllipse(0, 0, this->boundingRect().width(), this->boundingRect().height());
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
    update(0,0,SIZE,SIZE);
}

void LightWidget::setColor(const QColor &color)
{
    m_color = color;
}

void LightWidget::turnOff()
{
    setOn(false);
}

void LightWidget::turnOn()
{
    setOn(true);
}
