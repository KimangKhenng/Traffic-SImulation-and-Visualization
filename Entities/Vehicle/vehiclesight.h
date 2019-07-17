#ifndef VEHICLESIGHT_H
#define VEHICLESIGHT_H

#include <QGraphicsRectItem>
class Vehicle;
class VehicleSight :public QGraphicsRectItem
{
public:
    VehicleSight(const QRectF& rec,QGraphicsItem *parent = nullptr);
    Vehicle *vehicle() const;

private:
    Vehicle *m_vehicle;
};

#endif // VEHICLESIGHT_H
