#ifndef VEHICLESGENERATOR_H
#define VEHICLESGENERATOR_H

#include "Entities/Vehicle/vehicle.h"
#include "Utilities/road.h"
#include "commonenum.h"
///////////////
/// \brief The VehiclesGenerator class
/// FactoryClass For Vehicle Class
/// //////////
class VehiclesGenerator
{
public:
    static Vehicle *getLeftTurningVehicle(const region& approach,
                                          const VEHICLEMETHOD& x,
                                          const bool& vision= false,
                                          const bool& interact = true);

    static Vehicle *getThroughVehicle(const region& approach,
                                      const int& lane,
                                      const VEHICLEMETHOD& x,
                                      const bool& vision= false,
                                      const bool& interact = true);

    static Vehicle *getRightTurningVehicle(const region& approach,
                                           const VEHICLEMETHOD& x,
                                           const bool& vision = false,
                                           const bool& interact = true);
};

#endif // VEHICLESGENERATOR_H
