/**
 \addtogroup transport
 @{
 */

/**
 *
 * \defgroup   udp-conf UDP Configurations
 * @{
 * \file       udp-conf.h
 * \authors    Carlos Abreu
 *
 * \brief UDP Server/Client configurations.
 */

#ifndef __UDP_CONF__
#define __UDP_CONF__

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/

#define UDP_CLIENT_PORT 8765
#define UDP_SERVER_PORT 5678

#define SENSOR_TEMP 0
#define SENSOR_HUMI 1
#define SENSOR_BATT 2
#define SENSOR_RAD 3
#define SENSOR_LIGHT 4
#define SENSOR_ACEL_X 5
#define SENSOR_ACEL_Y 6
#define SENSOR_ACEL_Z 7
#define TEST 99

#define DATASIZE 16

#define SERVER_IP_ADDR(ipaddr) \
		uip_ip6addr(ipaddr, 0xaaaa, 0, 0, 0, 0x0212, 0x7401, 0x0001, 0x0101)

/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/

struct tcpip_msg
{
	uint8_t nodeid;
	uint32_t seqno;
	uint id;
	char data[DATASIZE];
	char min[DATASIZE];
	char max[DATASIZE];
	char avg[DATASIZE];
};
typedef struct tcpip_msg tcpip_msg_t;

/*******************************************************************************
*                             Function Prototypes                              *
*******************************************************************************/


/*******************************************************************************
*                             Process Prototypes                               *
*******************************************************************************/


/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
#endif /* __UDP_CONF__ */
/** @} */
/** @} */


