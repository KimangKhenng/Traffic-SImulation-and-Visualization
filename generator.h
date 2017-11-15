#ifndef GENERATOR_H
#define GENERATOR_H

#include <QtWidgets>
#include <QtCore>
#include "commonenum.h"
#include "vehiclesgenerator.h"
#include "simulationscene.h"
#define MAX_S_N 5
#define MAX_N_S 5
#define MAX_E_W 5
#define MAX_W_E 5

class Generator : public QObject
{
    Q_OBJECT
public:
    Generator(SimulationScene *scene);
    Generator();
    void setMethod(GENMETHOD x);
    void startGenerator();
    void setTimer(int x,int y,int c,int z);
    void setScene(SimulationScene *scene);
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
};

#endif // GENERATOR_H
