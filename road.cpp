#include "road.h"
#include <QtCore>
#include <QtWidgets>
road::road(QGraphicsScene *scene)
{
    m_path_4.moveTo(325,600);
    m_path_4.lineTo(325,328 + 30 +20);
    m_path_4.arcTo(225-150,282 + 30 - 50 ,100 + 150,100 + 150,5,75);
    m_path_4.lineTo(0,282 - 20);
    QBrush brush(Qt::blue);
    QPen pen;
    pen.setBrush (brush);
    setPen (pen);
    setPath(m_path_4);
    setTransformOriginPoint(0,0);
    setFlag(QGraphicsItem::ItemIsMovable);
}
