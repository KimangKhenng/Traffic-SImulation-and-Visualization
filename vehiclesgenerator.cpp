#include "vehiclesgenerator.h"

Vehicle *VehiclesGenerator::getLeftTurningVehicle(region approach)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getLeft(approach));
    p->setDirection(Direction::LEFT_TURNING);
    p->setRegion(approach);
    p->initialize();
    p->get_timer()->start(10);
    p->set_on_action(true);
    return p;

}

Vehicle *VehiclesGenerator::getThroughVehicle(region approach, int lane)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getThrough(approach,lane));
    p->setDirection(Direction::THROUGH);
    p->setRegion(approach);
    p->initialize();
    p->get_timer()->start(10);
    p->set_on_action(true);
    return p;
}

Vehicle *VehiclesGenerator::getRightTurningVehicle(region approach)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getRight(approach));
    p->setDirection(Direction::RIGHT_TURNING);
    p->setRegion(approach);
    p->initialize();
    p->get_timer()->start(10);
    p->set_on_action(true);
    return p;
}
