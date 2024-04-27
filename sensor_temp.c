#include "sensor_temp.h"

#define NUM_READINGS 10

static struct etimer temperatureTimer;
static int temperatureReadings[NUM_READINGS];
static int readingsCount = 0;
static int newTemperature = 0;

void startTemperatureSensor(void) {
    if (process_is_running(&sensor_temp)) {
        return;
    }
    process_start(&sensor_temp, NULL);
}

void stopTemperatureSensor(void) {
    if (!process_is_running(&sensor_temp)) {
        return;
    }
    process_exit(&sensor_temp);
}

int isTemperatureSensorRunning(void) {
    return process_is_running(&sensor_temp);
}

void updateTemperatureStats(int newTemp) {
    last_temp = newTemp;

    if (newTemp > max_temp) {
        max_temp = newTemp;
    }

    if (newTemp < min_temp) {
        min_temp = newTemp;
    }

    avg_temp = (avg_temp * readingsCount + newTemp) / (readingsCount + 1);

    temperatureReadings[readingsCount % NUM_READINGS] = newTemp;

    readingsCount++;
}

void printTemperatureStats() {
    printf("Temperature: %d.%u C\n", last_temp / 100, last_temp % 100);
    printf("Maximum Temperature: %d.%u C\n", max_temp / 100, max_temp % 100);
    printf("Minimum Temperature: %d.%u C\n", min_temp / 100, min_temp % 100);
    printf("Average Temperature: %d.%u C\n", avg_temp / 100, avg_temp % 100);
}

int getLastTemperature(void) {
    return last_temp;
}

int getMinTemperature(void) {
    return min_temp;
}

int getMaxTemperature(void) {
    return max_temp;
}

int getAvgTemperature(void) {
    return avg_temp;
}

PROCESS(sensor_temp, "EMECA TP3 Temperature");

PROCESS_THREAD(sensor_temp, ev, data) {
    PROCESS_BEGIN();

    #if CONTIKI_TARGET_Z1
        SENSORS_ACTIVATE(tmp102);
    #elif CONTIKI_TARGET_SKY
        SENSORS_ACTIVATE(sht11_sensor);
    #else
        printf("The chosen platform is not supported.\n");
    #endif

    etimer_set(&temperatureTimer, CLOCK_SECOND);

    while (1) {
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&temperatureTimer));

        #if CONTIKI_TARGET_Z1
            newTemperature = tmp102.value(TMP102_READ);
            printf("Z1 Temperature: %d.%u C\n", newTemperature / 100, newTemperature % 100);
        #elif CONTIKI_TARGET_SKY
            newTemperature = sht11_sensor.value((SHT11_SENSOR_TEMP / 10) - 396);
            printf("SKY Temperature: %d.%u C\n", newTemperature / 100, newTemperature % 100);
        #endif

        updateTemperatureStats(newTemperature);
        etimer_reset(&temperatureTimer);
    }

    PROCESS_END();
}
