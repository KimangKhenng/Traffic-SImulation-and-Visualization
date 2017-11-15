#include "generator.h"

Generator::Generator(SimulationScene *scene):m_scene(scene)
{

}

Generator::Generator():m_number_N_S(0),m_number_S_N(0),
    m_number_W_E(0),m_number_E_W(0),m_time_N_S(0),
    m_time_S_N(0),m_time_W_E(0),m_time_E_W(0)
{
    for(int i = 0 ; i < 4 ; ++i){
        m_timer.append( new QTimer());
    }
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void Generator::setMethod(GENMETHOD x)
{
    m_method = x;
}

void Generator::startGenerator()
{
    this->connect(m_timer.at(0),SIGNAL(timeout()),this,SLOT(makeEastWest()));
    this->connect(m_timer.at(1),SIGNAL(timeout()),this,SLOT(makeNorthSouth()));
    this->connect(m_timer.at(2),SIGNAL(timeout()),this,SLOT(makeSouthNorth()));
    this->connect(m_timer.at(3),SIGNAL(timeout()),this,SLOT(makeWestEast()));
    m_timer.at(0)->start(m_time_E_W);
    m_timer.at(1)->start(m_time_N_S);
    m_timer.at(2)->start(m_time_S_N);
    m_timer.at(3)->start(m_time_W_E);
}

void Generator::setTimer(int x, int y, int c, int z)
{
    m_time_N_S = x;
    m_time_S_N = y;
    m_time_E_W = c;
    m_time_W_E = z;
}

void Generator::makeNorthSouth()
{
    if(m_scene->getNumber(REGION_N_S) > MAX_N_S){
        return;
    }
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_N_S));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_N_S));
                //m_number_N_S++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_N_S));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,1));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2));
                //m_number_N_S++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,3));
                //m_number_N_S++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_N_S));
                //m_number_N_S++;
                break;
        }
            break;
    }
}

void Generator::makeSouthNorth()
{
    if(m_scene->getNumber(REGION_S_N) > MAX_S_N){
        return;
    }
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_S_N));
                //m_number_S_N++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2));
                //m_number_S_N++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_S_N));
                //m_number_S_N++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_S_N));
                //m_number_S_N++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,1));
                //m_number_S_N++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2));
                //m_number_S_N++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,3));
                //m_number_S_N++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_S_N));
                //m_number_S_N++;
                break;
        }
            break;
    }
}

void Generator::makeWestEast()
{
    if(m_scene->getNumber(REGION_W_E) > MAX_W_E){
        return;
    }
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_W_E));
                //m_number_W_E++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2));
               //m_number_W_E++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_W_E));
                //m_number_W_E++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_W_E));
                //m_number_W_E++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,1));
                //m_number_W_E++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2));
                //m_number_W_E++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,3));
                //m_number_W_E++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_W_E));
                //m_number_W_E++;
                break;
        }
            break;
    }
}

void Generator::makeEastWest()
{
    if(m_scene->getNumber(REGION_E_W) > MAX_E_W){
        return;
    }
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_E_W));
                //m_number_E_W++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2));
                //m_number_E_W++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_E_W));
                //m_number_E_W++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_E_W));
                //m_number_E_W++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,1));
                //m_number_E_W++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2));
                //m_number_E_W++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,3));
                //m_number_E_W++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_E_W));
                //m_number_E_W++;
                break;
        }
            break;
    }
}

void Generator::setScene(SimulationScene *scene)
{
    m_scene = scene;
}
