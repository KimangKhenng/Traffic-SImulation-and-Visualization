#ifndef COMMONENUM_H
#define COMMONENUM_H
#include <QDebug>
#include <QTimer>

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
#endif // COMMONENUM_H
