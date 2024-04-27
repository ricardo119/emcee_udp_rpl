#include "contiki.h"
#include <stdio.h>
#include "sys/etimer.h"

#if CONTIKI_TARGET_Z1
    //
#elif CONTIKI_TARGET_SKY
	#include "../dev/sht11/sht11-sensor.h"
#endif


void start_hum_sensor(void);
void stop_hum_sensor(void);
int get_hum(void);

PROCESS_NAME(sensor_hum);