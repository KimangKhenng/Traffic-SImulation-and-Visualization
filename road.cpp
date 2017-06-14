#include "road.h"
#include <QtCore>
#include <QtWidgets>
road::road(QGraphicsScene *scene)
{
    m_path_4.moveTo(410,600);
    m_path_4.lineTo(410,328);
    m_path_4.arcTo(310,282,100,100,0,78);
    m_path_4.lineTo(0,282);
    m_path_1.moveTo(scene->sceneRect().x()+10,600);
    m_path_1.lineTo(scene->sceneRect().x()+10,0);
    setPath(m_path_4);
    setTransformOriginPoint(0,0);
    setFlag(QGraphicsItem::ItemIsMovable);
}
