#include "vehiclesight.h"
#include "vehicle.h"
VehicleSight::VehicleSight(const QRectF &rec, QGraphicsItem *parent):QGraphicsRectItem (rec,parent),
    m_vehicle(dynamic_cast<Vehicle *>(parent))
{
    this->setBrush(Qt::NoBrush);
    this->setPen(QPen(QColor(Qt::black)));
}

Vehicle *VehicleSight::vehicle() const
{
    return m_vehicle;
}
