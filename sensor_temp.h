#include "contiki.h"
#include <stdio.h>
#include "sys/etimer.h"

#if CONTIKI_TARGET_Z1
	#include "dev/tmp102.h"
#elif CONTIKI_TARGET_SKY
	#include "../dev/sht11/sht11-sensor.h"
#endif

static int maxTemp = -9999;
static int minTemp = 9999;
static int lastTemp = 0;
static int avgTemp = 0;

void startTemperatureSensor(void);
void stopTemperatureSensor(void);
int isTemperatureSensorRunning(void);
int getLastTemperature(void);
int getMaxTemperature(void);
int getMinTemperature(void);
int getAvgTemperature(void);

PROCESS_NAME(sensor_temp);

