#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>
#include <QtCore>
#include "commonenum.h"
#include "vehiclesgenerator.h"
#include "simulationscene.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    Generator(SimulationScene *scene);
    Generator();
    void setMethod(GENMETHOD x);
    void startGenerator();
    void stopGenerator();
    void startAutoGeneraion();
    void setTimer(int x,int y,int c,int z);
    void setScene(SimulationScene *scene);
    void turnOn();
    void turnOff();
    void setMode(const VEHICLEMETHOD &mode);
public slots:
    void makeNorthSouth();
    void makeSouthNorth();
    void makeWestEast();
    void makeEastWest();
private:
    SimulationScene *m_scene;
    QList<QTimer*> m_timer;
    int m_number_N_S;
    int m_number_S_N;
    int m_number_W_E;
    int m_number_E_W;
    int m_time_N_S;
    int m_time_S_N;
    int m_time_W_E;
    int m_time_E_W;
    GENMETHOD m_method;
    VEHICLEMETHOD m_mode;
    bool m_running_state;
};

#endif // GENERATOR_H