#include "vehiclesgenerator.h"

Vehicle *VehiclesGenerator::getLeftTurningVehicle(const region &approach, const VEHICLEMETHOD &x)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getLeft(approach));
    p->setDirection(Direction::LEFT_TURNING);
    p->setRegion(approach);
    p->initialize();
    p->setMode(x);
    p->setScale(0.8);
//    p->get_timer()->start(10);
//    p->set_on_action(true);
    return p;

}

Vehicle *VehiclesGenerator::getThroughVehicle(const region &approach, const int &lane, const VEHICLEMETHOD &x)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getThrough(approach,lane));
    p->setDirection(Direction::THROUGH);
    p->setRegion(approach);
    p->initialize();
    p->setMode(x);
    p->setScale(0.8);
//    p->get_timer()->start(10);
//    p->set_on_action(true);
    return p;
}

Vehicle *VehiclesGenerator::getRightTurningVehicle(const region &approach, const VEHICLEMETHOD &x)
{
    Vehicle *p = new Vehicle();
    p->extract_coordinate(road::getRight(approach));
    p->setDirection(Direction::RIGHT_TURNING);
    p->setRegion(approach);
    p->initialize();
    p->setMode(x);
    p->setScale(0.8);
//    p->get_timer()->start(10);
//    p->set_on_action(true);
    return p;
}
