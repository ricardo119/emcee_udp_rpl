#include "contiki.h"
#include <stdio.h>
#include "sys/etimer.h"

#if CONTIKI_TARGET_Z1
    #include "../dev/adxl345.h"
#endif

//*******************ACC X*******************//
static int max_Xaxis = -9999;
static int min_Xaxis = 9999;
static int last_Xaxis = 0;
static int avg_Xaxis = 0;

//*******************ACC Y*******************//
static int max_Yaxis = -9999;
static int min_Yaxis = 9999;
static int last_Yaxis = 0;
static int avg_Yaxis = 0;

//*******************ACC Z*******************//
static int max_Zaxis = -9999;
static int min_Zaxis = 9999;
static int last_Zaxis = 0;
static int avg_Zaxis = 0;


void startAccSensor(void);
void stopAccSensor(void);
int isAccSensorRunning(void);
//*******************ACC X*******************//
int getAccX(void);
int getMaxAccX(void);
int getMinAccX(void);
int getAvgAccX(void);

//*******************ACC Y*******************//
int getAccY(void);
int getMaxAccY(void);
int getMinAccY(void);
int getAvgAccY(void);

//*******************ACC Z*******************//
int getAccZ(void);
int getMaxAccZ(void);
int getMinAccZ(void);
int getAvgAccZ(void);

PROCESS_NAME(sensor_acc);
