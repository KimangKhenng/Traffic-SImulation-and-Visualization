#ifndef VEHICLESGENERATOR_H
#define VEHICLESGENERATOR_H

#include "vehicle.h"
#include <QtCore>
#include <QtWidgets>
#include "road.h"
#include "trafficlight.h"
///////////////
/// \brief The VehiclesGenerator class
/// FactoryClass For Vehicle Class
/// //////////
class VehiclesGenerator
{
public:
    static Vehicle *getLeftTurningVehicle(region approach);
    static Vehicle *getThroughVehicle(region approach,int lane);
    static Vehicle *getRightTurningVehicle(region approach);
};

#endif // VEHICLESGENERATOR_H
