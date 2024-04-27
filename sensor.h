

/**
 \addtogroup application
 @{
 */

/**
 * \defgroup   sensor Sensor
 * @{
 * \file       sensor.h
 * \authors    Carlos Abreu
 *
 * \brief Body sensor
 */

#include "contiki.h"
#include "dev/button-sensor.h"
#include "dev/leds.h"

// Sensors libraries by funcionality
#include "sensor_acc.h"
#include "sensor_temp.h"
#include "sensor_hum.h"
#include "sensor_light.h"


#include "udp-client.h"
#include "node-id.h"

#ifndef DEBUG
#define DEBUG DEBUG_NONE
   #include "net/ip/uip-debug.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __TEMPERATURE_SENSOR__
#define __TEMPERATURE_SENSOR__

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/

#ifdef CONF_SEND_INTERVAL
	#define SEND_INTERVAL   CONF_SEND_INTERVAL
#else
	#define SEND_INTERVAL   CLOCK_SECOND * 1
#endif

#ifdef CONF_SETUP_INTERVAL
	#define SETUP_INTERVAL   CONF_SETUP_INTERVAL
#else
	#define SETUP_INTERVAL   CLOCK_SECOND * 30
#endif

/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/


/*******************************************************************************
*                             Function Prototypes                              *
*******************************************************************************/


/*******************************************************************************
*                              Process Prototypes                              *
*******************************************************************************/

PROCESS_NAME(sensor_process);

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
#endif /* __TEMPERATURE_SENSOR__ */
/** @} */
/** @} */


