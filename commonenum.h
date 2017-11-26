#ifndef COMMONENUM_H
#define COMMONENUM_H

////////////////
#ifndef MAX_S_N
    #define MAX_S_N 10
#endif
////////////////
#ifndef MAX_N_S
    #define MAX_N_S 10
#endif
///////////////
#ifndef MAX_E_W
    #define MAX_E_W 10
#endif
//////////////
#ifdef MAX_W_E
    #define MAX_W_E 10
#endif
///////////////
#ifndef TIME_UNIT
    #define TIME_UNIT 5
#endif
////////////////

enum Direction{LEFT_TURNING,THROUGH,RIGHT_TURNING};
enum region{REGION_E_W,REGION_N_S,REGION_W_E,REGION_S_N};
enum GENMETHOD{GEN_3,GEN_5,NO_TURN};
enum TRAFFICMODE{NO_SIGNAL,HAS_SIGNAL};
enum VEHICLEMETHOD{SIGHTSEEING,GO_THROUGH};

#endif // COMMONENUM_H
