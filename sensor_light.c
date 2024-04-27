#include "sensor_light.h"

#define NUM_READINGS 10

static struct etimer timer;
static int photoReadings[NUM_READINGS];
static int readingsCount = 0;
static int newPhotoReading = 0;

void startLightSensor(void) {
    if (process_is_running(&sensor_light)) {
        return;
    }
    process_start(&sensor_light, NULL);
}

void stopLightSensor(void) {
    if (!process_is_running(&sensor_light)) {
        return;
    }
    process_exit(&sensor_light);
}

int isLightSensorRunning(void) {
    return process_is_running(&sensor_light);
}

void updatePhotoStatistics(int newPhoto) {

    lastPhoto = newPhoto;

    if (newPhoto > maxPhoto) {
        maxPhoto = newPhoto;
    }

    if (newPhoto < minPhoto) {
        minPhoto = newPhoto;
    }

    avgPhoto = (avgPhoto * readingsCount + newPhoto) / (readingsCount + 1);

    photoReadings[readingsCount % NUM_READINGS] = newPhoto;

    readingsCount++;
}

void printPhotoStatistics(void){
    printf("Current Photosynthetic Light: %d\n", lastPhoto);
    printf("Maximum Photosynthetic Light: %d\n", maxPhoto);
    printf("Minimum Photosynthetic Light: %d\n", minPhoto);
    printf("Average Photosynthetic Light: %d\n", avgPhoto);
}

int getLastPhotoLight(void){
    return lastPhoto;
}

int getMinPhotoLight(void){
    return minPhoto;
}

int getMaxPhotoLight(void){
    return maxPhoto;
}

int getAvgPhotoLight(void){
    return avgPhoto;
}

PROCESS(sensor_light, "EMECA TP3 Light Sensor");

PROCESS_THREAD(sensor_light, ev, data) {
    PROCESS_BEGIN();

    #if CONTIKI_TARGET_SKY
        SENSORS_ACTIVATE(light_sensor);
    #else
        printf("The chosen platform is not supported.\n");
    #endif 

    etimer_set(&timer, CLOCK_SECOND);

    while (1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&timer));

        #if CONTIKI_TARGET_Z1
            printf("Z1 platform doesn't have a light sensor.\n");
        #elif CONTIKI_TARGET_SKY
            newPhotoReading = light_sensor.value(LIGHT_SENSOR_PHOTOSYNTHETIC);
            printf("Sky Light (Photosynthetic): %d\n", newPhotoReading);
        #endif

        updatePhotoStatistics(newPhotoReading);
        etimer_reset(&timer);
    }

    PROCESS_END();
}
