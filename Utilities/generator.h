#ifndef GENERATOR_H
#define GENERATOR_H


#include "vehiclesgenerator.h"
#include "UI/simulationscene.h"

class Generator : public QObject
{
    Q_OBJECT
public:
    Generator(SimulationScene *scene);
    Generator();
    ~Generator();
    void setMethod(const GENMETHOD& x);
    void startGenerator();
    void stopGenerator();
    void startAutoGeneraion();
    void setTimer(const int& N_S,const int& S_N,const int& E_W,const int& W_E);
    void setScene(SimulationScene *scene);
    void turnOn();
    void turnOff();
    void setMode(const VEHICLEMETHOD &mode);
    void setVisionOn(const bool& vision);
    void setInteraction(const bool& interact);
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
    bool m_VisionOn;
    bool m_IsInteraction;
};

#endif // GENERATOR_H
