#include "generator.h"

Generator::Generator(SimulationScene *scene):m_scene(scene),m_mode(VEHICLEMETHOD::GO_THROUGH),m_running_state(false)
{
    for(int i = 0 ; i < 4 ; ++i){
        m_timer.append( new QTimer());
    }
    //qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
}

Generator::Generator():m_number_N_S(0),m_number_S_N(0),
    m_number_W_E(0),m_number_E_W(0),m_time_N_S(0),
    m_time_S_N(0),m_time_W_E(0),m_time_E_W(0),m_mode(VEHICLEMETHOD::GO_THROUGH),m_running_state(false)
{
    for(int i = 0 ; i < 4 ; ++i){
        m_timer.append( new QTimer());
    }
    //qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
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

void Generator::stopGenerator()
{
    this->disconnect(m_timer.at(0),SIGNAL(timeout()),this,SLOT(makeEastWest()));
    this->disconnect(m_timer.at(1),SIGNAL(timeout()),this,SLOT(makeNorthSouth()));
    this->disconnect(m_timer.at(2),SIGNAL(timeout()),this,SLOT(makeSouthNorth()));
    this->disconnect(m_timer.at(3),SIGNAL(timeout()),this,SLOT(makeWestEast()));
}

void Generator::startAutoGeneraion()
{
    int x = 2000;
    int y = 3000;
    int z = 3500;
    int v = 2900;
    setTimer(x,y,z,v);
    QTimer *t1 = new QTimer();
    this->connect(t1,SIGNAL(timeout()),this,SLOT(makeEastWest()));
    t1->start (x);
    QTimer *t2 = new QTimer();
    this->connect(t2,SIGNAL(timeout()),this,SLOT(makeNorthSouth()));
    t2->start (y);
    QTimer *t3 = new QTimer();
    this->connect(t3,SIGNAL(timeout()),this,SLOT(makeSouthNorth()));
    t3->start (z);
    QTimer *t4 = new QTimer();
    this->connect(t4,SIGNAL(timeout()),this,SLOT(makeWestEast()));
    t4->start (v);
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
    //qDebug()<<"Hello";
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_N_S,m_mode));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2,m_mode));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_N_S,m_mode));
                //m_number_N_S++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_N_S,m_mode));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,1,m_mode));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2,m_mode));
                //m_number_N_S++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,3,m_mode));
                //m_number_N_S++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_N_S,m_mode));
                //m_number_N_S++;
                break;
        }
            break;
        case NO_TURN:
            switch (qrand()%3){
                case 0:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,1,m_mode));
                    //m_number_N_S++;
                    break;
                case 1:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2,m_mode));
                    //m_number_N_S++;
                    break;
                case 2:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,3,m_mode));
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
    //qDebug()<<"Hello";
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_S_N,m_mode));
                //m_number_S_N++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2,m_mode));
                //m_number_S_N++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_S_N,m_mode));
                //m_number_S_N++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_S_N,m_mode));
                //m_number_S_N++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,1,m_mode));
                //m_number_S_N++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2,m_mode));
                //m_number_S_N++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,3,m_mode));
                //m_number_S_N++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_S_N,m_mode));
                //m_number_S_N++;
                break;
            }
            break;
        case NO_TURN:
            switch (qrand()%3){
                case 0:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,1,m_mode));
                    //m_number_N_S++;
                    break;
                case 1:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2,m_mode));
                    //m_number_N_S++;
                    break;
                case 2:
                    m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,3,m_mode));
                    //m_number_N_S++;
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
    //qDebug()<<"Hello";
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_W_E,m_mode));
                //m_number_W_E++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2,m_mode));
               //m_number_W_E++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_W_E,m_mode));
                //m_number_W_E++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_W_E,m_mode));
                //m_number_W_E++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,1,m_mode));
                //m_number_W_E++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2,m_mode));
                //m_number_W_E++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,3,m_mode));
                //m_number_W_E++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_W_E,m_mode));
                //m_number_W_E++;
                break;
        }
            break;
    case NO_TURN:
        switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,1,m_mode));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2,m_mode));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,3,m_mode));
                //m_number_N_S++;
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
    //qDebug()<<"Hello";
    switch (m_method) {
        case GEN_3:
            switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_E_W,m_mode));
                //m_number_E_W++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2,m_mode));
                //m_number_E_W++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_E_W,m_mode));
                //m_number_E_W++;
                break;
        }
            break;
        case GEN_5:
            switch (qrand()%5){
            case 0:
                m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_E_W,m_mode));
                //m_number_E_W++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,1,m_mode));
                //m_number_E_W++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2,m_mode));
                //m_number_E_W++;
                break;
            case 3:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,3,m_mode));
                //m_number_E_W++;
                break;
            case 4:
                m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_E_W,m_mode));
                //m_number_E_W++;
                break;
        }
            break;
    case NO_TURN:
        switch (qrand()%3){
            case 0:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,1,m_mode));
                //m_number_N_S++;
                break;
            case 1:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2,m_mode));
                //m_number_N_S++;
                break;
            case 2:
                m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,3,m_mode));
                //m_number_N_S++;
                break;
        }
        break;

    }
}

void Generator::setMode(const VEHICLEMETHOD &mode)
{
    m_mode = mode;
}

void Generator::setScene(SimulationScene *scene)
{
    m_scene = scene;
}

void Generator::turnOn()
{
    m_running_state = true;
}

void Generator::turnOff()
{
    m_running_state = false;
}
