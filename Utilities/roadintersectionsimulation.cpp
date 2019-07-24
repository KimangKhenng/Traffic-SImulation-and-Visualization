#include "roadintersectionsimulation.h"
#include <QDebug>
RoadIntersectionSimulation::RoadIntersectionSimulation(QGraphicsView *view)
    :m_Scene(new SimulationScene)
    ,m_SimulationState(false)
    ,m_TrafficLightOn(false)
    ,m_VehicleSightSeeingOn(false)
    ,m_VisualizationOn(false)
    ,m_SimulationTimer(new QTimer)
{
    m_Generator = new Generator(m_Scene);
    QObject::connect(m_SimulationTimer,SIGNAL(timeout()),this,SLOT(updateVehicle()));
    view->setScene(m_Scene);
    m_Scene->setSceneRect(0,0,800,600);
}

RoadIntersectionSimulation::~RoadIntersectionSimulation()
{
    delete m_Scene;
    delete m_Generator;
    delete m_SimulationTimer;
}

void RoadIntersectionSimulation::startSimulation(const int &B_NS,
                                                 const int &B_SN,
                                                 const int &B_WE,
                                                 const int &B_EW,
                                                 const int &RED_LIGHT,
                                                 const int &GREEN_LIGHT,
                                                 const int &LEFT_GREEN_LIGHT,
                                                 const int &YELLOW_LIGHT, const GENMETHOD &METh, const VEHICLEMETHOD &MODE)
{


    m_Generator->setTimer(B_NS,B_SN,B_EW,B_WE);
    m_Generator->setMethod(METh);
    m_Generator->setMode(MODE);
    m_Scene->getController()->setLightDuration(GREEN_LIGHT,LEFT_GREEN_LIGHT,YELLOW_LIGHT,RED_LIGHT);
    m_Scene->getController()->startTrafficLightAll();
    m_Scene->showTrafficLight();
    m_SimulationTimer->start(TIME_STEP);
    m_Generator->startGenerator();
}

void RoadIntersectionSimulation::stopSimulation()
{
    m_SimulationTimer->stop();
    m_Generator->stopGenerator();
    m_Scene->getController()->stopTrafficLightAll();
}

void RoadIntersectionSimulation::updateVehicle()
{
    m_Scene->updateScene(VEHICLEMETHOD::SIGHTSEEING);
}

SimulationScene *RoadIntersectionSimulation::Scene() const
{
    return m_Scene;
}
