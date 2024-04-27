#include "sensor_acc.h"

#define NUM_READINGS 10

static struct etimer accTimer;
static int XaxisReadings[NUM_READINGS];
static int YaxisReadings[NUM_READINGS];
static int ZaxisReadings[NUM_READINGS];
static int readingsCount = 0;

void startAccSensor(void){
	if (process_is_running(&sensor_acc)) {
        return;
    }
	process_start(&sensor_acc, NULL);
}

void stopAccSensor(void){
	if (!process_is_running(&sensor_acc)) {
        return;
    }
	process_exit(&sensor_acc);
}

int isAccSensorRunning(void){
    return process_is_running(&sensor_acc);
}

void updateXstats(int newXaxis){

    last_Xaxis = newXaxis;

    if(newXaxis > max_Xaxis){
        max_Xaxis = newXaxis;
    }

    if(newXaxis < min_Xaxis){
        min_Xaxis = newXaxis;
    }

    avg_Xaxis = (avg_Xaxis * readingsCount + newXaxis) / (readingsCount + 1);

    XaxisReadings[readingsCount % NUM_READINGS] = newXaxis;

    readingsCount++;
}

void updateYstats(int newYaxis){

    last_Yaxis = newYaxis;

    if(newYaxis > max_Yaxis){
        max_Yaxis = newYaxis;
    }

    if(newYaxis < min_Yaxis){
        min_Yaxis = newYaxis;
    }

    avg_Yaxis = (avg_Yaxis * readingsCount + newYaxis) / (readingsCount + 1);

    YaxisReadings[readingsCount % NUM_READINGS] = newYaxis;

    readingsCount++;
}

void updateZstats(int newZaxis){

    last_Zaxis = newZaxis;

    if(newZaxis > max_Zaxis){
        max_Zaxis = newZaxis;
    }

    if(newZaxis < min_Zaxis){
        min_Zaxis = newZaxis;
    }

    avg_Zaxis = (avg_Zaxis * readingsCount + newZaxis) / (readingsCount + 1);

    ZaxisReadings[readingsCount % NUM_READINGS] = newZaxis;

    readingsCount++;
}

//*******************ACC X*******************//
int getAccX(void){
    return x_axis;
}

int getMaxAccX(void){
    return max_Xaxis;
}

int getMinAccX(void){
    return min_Xaxis;
}

int getAvgAccX(void){
    return avg_Xaxis;
}

//*******************ACC Y*******************//
int getAccY(void){
    return y_axis;
}

int getMaxAccY(void){
    return max_Yaxis;
}

int getMinAccY(void){
    return min_Yaxis;
}

int getAvgAccY(void){
    return avg_Yaxis;
}
//*******************ACC Z*******************//
int getAccZ(void){
    return z_axis;
}

int getMaxAccZ(void){
    return max_Zaxis;
}

int getMinAccZ(void){
    return min_Zaxis;
}

int getAvgAccZ(void){
    return avg_Zaxis;
}

PROCESS(sensor_acc, "Accelerometer");

PROCESS_THREAD(sensor_acc, ev, data){

    PROCESS_BEGIN();

    #if CONTIKI_TARGET_Z1
        SENSORS_ACTIVATE(adxl345);
    #else 
        printf("The chosen platform is not supported.\n");
    #endif

    etimer_set(&accTimer, CONF_TEMP_READINGS);

    while(1){
        PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&accTimer));

        #if CONTIKI_TARGET_Z1
            x_axis = adxl345.value(X_AXIS);
            y_axis = adxl345.value(Y_AXIS);
            z_axis = adxl345.value(Z_AXIS);

            printf("Z1 Acceleration: X %d Y %d Z %d\n", x_axis, y_axis, z_axis);
        #elif CONTIKI_TARGET_SKY
            printf("Sky platform doesn't have an accelerometer.\n");
            PROCESS_EXIT();
        #endif

        updateXstats(x_axis);
        updateYstats(y_axis);
        updateZstats(z_axis);
        etimer_reset(&accTimer);
    }

    PROCESS_END();
}
