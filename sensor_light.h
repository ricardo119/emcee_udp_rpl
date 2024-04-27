#include "contiki.h"
#include <stdio.h>
#include "sys/etimer.h"

#if CONTIKI_TARGET_SKY
	#include "../dev/light-sensor.h"
#endif

static int maxPhoto = -9999;
static int minPhoto = 9999;
static int lastPhoto = 0;
static int avgPhoto = 0;


void startLightSensor(void);
void stopLightSensor(void);
int isLightSensorRunning(void);
int getLastPhotoLight(void);
int getMaxPhotoLight(void);
int getMinPhotoLight(void);
int getAvgPhotoLight(void);

PROCESS_NAME(sensor_light);

