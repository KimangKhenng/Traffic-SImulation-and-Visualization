#include "vehiclesight.h"
#include "vehicle.h"
VehicleSight::VehicleSight(const QRectF &rec, QGraphicsItem *parent)
    :QGraphicsRectItem (rec,parent)
    ,m_vehicle(dynamic_cast<Vehicle *>(parent))
{
    this->setBrush(Qt::NoBrush);
    QPen tick;
    tick.setWidth(1);
    tick.setColor(Qt::black);
    this->setPen(tick);
}

Vehicle *VehicleSight::vehicle() const
{
    return m_vehicle;
}
