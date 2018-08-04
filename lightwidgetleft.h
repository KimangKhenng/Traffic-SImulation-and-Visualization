#ifndef LIGHTWIDGETLEFT_H
#define LIGHTWIDGETLEFT_H

#include "lightwidget.h"

class LightWidgetLeft : public LightWidget
{
public:
    LightWidgetLeft(const QColor &color,QGraphicsItem *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // LIGHTWIDGETLEFT_H
