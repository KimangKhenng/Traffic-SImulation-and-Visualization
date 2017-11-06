#ifndef LIGHTWIDGETLEFT_H
#define LIGHTWIDGETLEFT_H

#include "lightwidget.h"

class LightWidgetLeft : public LightWidget
{
public:
    LightWidgetLeft(const QColor &color,LightWidget *parent = 0);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // LIGHTWIDGETLEFT_H
