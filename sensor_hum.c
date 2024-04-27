#include "sensor_hum.h"

static struct etimer t;
static int hum = 0;

void start_hum_sensor(void){
	if (process_is_running(&sensor_hum)) return;
	process_start(&sensor_hum, NULL);
}

void stop_hum_sensor(void){
	if (!process_is_running(&sensor_hum)) return;
	process_exit(&sensor_hum);
}

int get_hum(void){
	return hum;
}

PROCESS(sensor_hum, "EMECA TP3 Humidity");

PROCESS_THREAD(sensor_hum, ev, data){


	PROCESS_BEGIN();

    #if CONTIKI_TARGET_SKY
        SENSORS_ACTIVATE(sht11_sensor);
    #else
        printf("The plataform choosed is not supported\n");
    #endif

    etimer_set(&t, CLOCK_SECOND);

    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&t));

        #if CONTIKI_TARGET_Z1
            printf("Z1 doens't have humidity sensor");
        #elif CONTIKI_TARGET_SKY
            hum = sht11_sensor.value(SHT11_SENSOR_HUMIDITY);
            printf("Sky Humidity: %d.%u %\n", hum / 100, hum % 100);
        #endif

        etimer_reset(&t);

    }
 
    PROCESS_END();

}