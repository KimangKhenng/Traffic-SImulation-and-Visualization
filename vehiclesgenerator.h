#ifndef VEHICLESGENERATOR_H
#define VEHICLESGENERATOR_H

#include "vehicle.h"
#include <QtCore>
#include <QtWidgets>
#include "road.h"
#include "commonenum.h"
///////////////
/// \brief The VehiclesGenerator class
/// FactoryClass For Vehicle Class
/// //////////
class VehiclesGenerator
{
public:
    static Vehicle *getLeftTurningVehicle(region approach,VEHICLEMETHOD x);
    static Vehicle *getThroughVehicle(region approach,int lane,VEHICLEMETHOD x);
    static Vehicle *getRightTurningVehicle(region approach,VEHICLEMETHOD x);
};

#endif // VEHICLESGENERATOR_H
