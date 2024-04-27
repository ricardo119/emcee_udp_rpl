/**
 * \addtogroup sensor
 * @{
 * \file       sensor.c 
 * \authors    Carlos Abreu
 *
 * \brief Body sensor.
 */

#include "sensor.h"

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/


/*******************************************************************************
*                               Global Variables                               *
*******************************************************************************/

static uint32_t maxseqnum = 500000;

static tcpip_msg_t temp_out_msg;
static tcpip_msg_t temp_imput_msg;

/*******************************************************************************
*                                  Functions                                   *
*******************************************************************************/

static void send_packet(uint32_t seqno, uint id, uint16_t data, uint16_t min, uint16_t max, uint16_t avg){
   	if(seqno >= maxseqnum) return;

	 // SENSORS WITH VALUES ROUNDED TO UNITS
    if (id == SENSOR_ACEL_X || id == SENSOR_ACEL_Y || id == SENSOR_ACEL_Z || id == SENSOR_LIGHT){
        memset(&tempOutputMessage, '\0', sizeof(tempOutputMessage));
        tempOutputMessage.nodeId = node_id;
        tempOutputMessage.sequenceNumber = sequenceNumber;
        tempOutputMessage.id = id;
        sprintf(tempOutputMessage.data, "%d", data);
        sprintf(tempOutputMessage.min, "%d", min);
        sprintf(tempOutputMessage.max, "%d", max);
        sprintf(tempOutputMessage.avg, "%d", avg);
    }

    // SENSORS WITH VALUES ROUNDED TO TENTHS
    else{
        memset(&tempOutputMessage, '\0', sizeof(tempOutputMessage));
        tempOutputMessage.nodeId = node_id;
        tempOutputMessage.sequenceNumber = sequenceNumber;
        tempOutputMessage.id = id;
        sprintf(tempOutputMessage.data, "%d.%u", data / 10, data % 10);
        sprintf(tempOutputMessage.min, "%d.%u", min / 10, min % 10);
        sprintf(tempOutputMessage.max, "%d.%u", max / 10, max % 10);
        sprintf(tempOutputMessage.avg, "%d.%u", avg / 10, avg % 10);
    }

    PRINTF("T: NodeID:%d SeqN:%lu DATA:%s MED:%s MIN:%s MAX:%s \n",
        tempOutputMessage.nodeId,
        tempOutputMessage.sequenceNumber,
        tempOutputMessage.data,
        tempOutputMessage.avg,
        tempOutputMessage.min,
        tempOutputMessage.max);
	
	return;
}

static void udp_app_call(char *data, uip_ipaddr_t* srcipaddr){
	memset(&temp_imput_msg, '\0', sizeof(temp_imput_msg));
	memcpy(&temp_imput_msg, data, sizeof(temp_imput_msg));
	
	 PRINTF("T: NodeID:%d SeqN:%lu DATA:%s MED:%s MIN:%s MAX:%s \n",
        tempInputMessage.nodeId,
        tempInputMessage.sequenceNumber,
        tempInputMessage.data,
        tempInputMessage.avg,
        tempInputMessage.min,
        tempInputMessage.max);
	
	return;
}

/*******************************************************************************
*                                  Processes                                   *
*******************************************************************************/

PROCESS(sensor_process, "Sensor process");
AUTOSTART_PROCESSES(&sensor_process);

PROCESS_THREAD(sensor_process, ev, data){
	PROCESS_BEGIN();
	PRINTF("SENSOR STARTED ...\n");

	SENSORS_ACTIVATE(button_sensor);
	
	udp_client_start();
	udp_client_add_listener(&udp_app_call);
	PROCESS_PAUSE();

	static uint32_t cnt = 0;
	uint32_t aux = 0;
	static struct etimer t;
	etimer_set(&t, SETUP_INTERVAL);

	PROCESS_WAIT_UNTIL(etimer_expired(&t));
	etimer_set(&t, SEND_INTERVAL);

	startTemperatureSensor();
	startPhotolightSensor();
	startAccelerometerSensor();
	
	while(1){
		if(etimer_expired(&t)){

			//*******************TEMPERATURE*******************//
			aux = cnt++;
			
			data = getLastTemperature();

			max = getMaxTemperature();

			min = getMinTemperature();

			avg = getAvgTemperature();

			send_packet(aux,SENSOR_TEMP,data,min,max,avg);		

			//*********PHOTOLIGHT*********//
			aux = cnt++;

			data = getLastPhotolight();

			max = getMaxPhotolight();

			min = getMinPhotolight();

			avg = getAvgPhotolight();

			send_packet(aux,SENSOR_LIGHT,data,min,max,avg);

			//*********ACCELEROMETER X*********//
			aux = cnt++;

			data = getAccX();

			max = getMaxAccX();

			min = getMinAccX();

			avg = getAvgAccX();

			send_packet(aux,SENSOR_ACEL_X,data,min,max,avg);

			//*********ACCELEROMETER Y*********//
			aux = cnt++;

			data = getAccY();

			max = getMaxAccY();

			min = getMinAccY();

			avg = getAvgAccY();

			send_packet(aux,SENSOR_ACEL_Y,data,min,max,avg);

			//*********ACCELEROMETER Z*********//
			aux = cnt++;

			data = getAccZ();

			max = getMaxAccZ();

			min = getMinAccZ();

			avg = getAvgAccZ();

			send_packet(aux,SENSOR_ACEL_Z,data,min,max,avg);

			etimer_restart(&t);
		}

		if(ev == sensors_event && data == &button_sensor)
		{
			leds_toggle(LEDS_GREEN);
			aux = cnt++;
			send_packet(0,TEST,0,0,0,0);
		}

		PROCESS_YIELD();
	}

	PROCESS_END();
}
/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
/** @} */
