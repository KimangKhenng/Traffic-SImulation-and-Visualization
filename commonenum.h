#ifndef COMMONENUM_H
#define COMMONENUM_H
#include <QDebug>
#include <QTimer>
#include <QTime>
#define PARALLEL_OMP 0
#define PARALLEL_CONCURRENT 0


////////////////
#ifndef MAX_S_N
    #define MAX_S_N 20
#endif
////////////////
#ifndef MAX_N_S
    #define MAX_N_S 20
#endif
///////////////
#ifndef MAX_E_W
    #define MAX_E_W 20
#endif
//////////////
#ifndef MAX_W_E
    #define MAX_W_E 20
#endif
///////////////
#ifndef TIME_UNIT
    #define TIME_UNIT 1/60 // refresh rate 60HZ
#endif
////////////////
/// \brief The Direction enum
enum SimulationState{STARTED,STOPPED,PAUSED,UNINITIALIZED,INITIALIZED};

enum Direction{LEFT_TURNING,THROUGH,RIGHT_TURNING};

enum region{REGION_E_W,REGION_N_S,REGION_W_E,REGION_S_N};

enum GENMETHOD{GEN_3,GEN_5,NO_TURN,ONLY_TURN};

enum TRAFFICMODE{NO_SIGNAL,HAS_SIGNAL};

enum VEHICLEMETHOD{SIGHTSEEING,GO_THROUGH};

enum STATE_MACHINE{Green_Going_Left,Left_Going_Yellow,Yellow_Going_Red,Red_Going_Yellow,Yellow_Going_Green};

struct SimulationInput{
    int B_NS = 3500;
    int B_SN = 3000;
    int B_WE = 3900;
    int B_EW = 3600;
    int RED_LIGHT = 5000;
    int GREEN_LIGHT = 3500;
    int LEFT_GREEN_LIGHT = 1500;
    int YELLOW_LIGHT = 500;
    GENMETHOD METh = GENMETHOD::GEN_3;
    VEHICLEMETHOD MODE = VEHICLEMETHOD::SIGHTSEEING;
    bool ShowTrafficLight = true;
    void trafficEasy()
    {
        B_NS = 4000;
        B_SN = 3500;
        B_WE = 3900;
        B_EW = 4100;
    }
    void trafficModerate(){
        B_NS = 2500;
        B_SN = 2000;
        B_WE = 2900;
        B_EW = 2500;
    }
    void trafficBusy(){
        B_NS = 1700;
        B_SN = 1900;
        B_WE = 1900;
        B_EW = 1600;
    }
    void LightingQuick(){
        RED_LIGHT = 3000;
        GREEN_LIGHT = 2000;
        LEFT_GREEN_LIGHT = 1000;
        YELLOW_LIGHT = 500;
    }
    void LightingModerate(){
        RED_LIGHT = 5000;
        GREEN_LIGHT = 3500;
        LEFT_GREEN_LIGHT = 1500;
        YELLOW_LIGHT = 500;
    }
    void LightingLong(){
        RED_LIGHT = 7000;
        GREEN_LIGHT = 5000;
        LEFT_GREEN_LIGHT = 2000;
        YELLOW_LIGHT = 500;
    }
    void ExperimentalCrazy(){
        B_NS = 500;
        B_SN = 700;
        B_WE = 900;
        B_EW = 200;
        METh = GENMETHOD::GEN_5;
        MODE = VEHICLEMETHOD::GO_THROUGH;
        ShowTrafficLight = false;
    }
    void ExperimentalFreeForAll(){
        trafficModerate();
        LightingModerate();
        ShowTrafficLight = false;
    }
    void random(){
        qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
        switch (qrand()%2) {
        case 0:
            switch (qrand()%3) {
            case 0:
                trafficEasy();
                break;
            case 1:
                trafficModerate();
                break;
            case 2:
                trafficBusy();
                break;
            }
            switch (qrand()%3) {
            case 0:
                LightingQuick();
                break;
            case 1:
                LightingModerate();
                break;
            case 2:
                LightingLong();
                break;
            }
            break;
        case 1:
            switch (qrand()%2) {
            case 0:
                ExperimentalCrazy();
                break;
            case 1:
                ExperimentalFreeForAll();
                break;
            }
            break;
        }

    }
};


#endif // COMMONENUM_H
