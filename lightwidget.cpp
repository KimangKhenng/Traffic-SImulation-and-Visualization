#include "lightwidget.h"

LightWidget::LightWidget(const QColor &color, QWidget *parent):m_color(color), m_on(false),
    QWidget(parent)
{

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
    update();
}

void LightWidget::turnOff()
{
    setOn(false);
}

void LightWidget::turnOn()
{
    setOn (true);
}

void LightWidget::paintEvent(QPaintEvent *)
{
    if (!m_on)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawEllipse(0, 0, width(), height());
}
