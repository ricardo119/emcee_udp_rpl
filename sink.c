/**
 * \addtogroup sink
 * @{
 * \file       sink.c 
 * \authors    Carlos Abreu
 *
 * \brief Sink Node.
 */

#include "sink.h"

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/


/*******************************************************************************
*                               Global Variables                               *
*******************************************************************************/

//static tcpip_msg_t temp_out_msg;
static tcpip_msg_t temp_imput_msg;

/*******************************************************************************
*                                  Functions                                   *
*******************************************************************************/

static void udp_app_call(char *data, uip_ipaddr_t* srcipaddr)
{
	memset(&temp_imput_msg, '\0', sizeof(temp_imput_msg));
	memcpy(&temp_imput_msg, data, sizeof(temp_imput_msg));

	if (temp_imput_msg.nodeid <= 0) return;

	PRINTF("SOF R: NodeID %d SeqN %lu DATA %s EOF\n",
		temp_imput_msg.nodeid, 
		temp_imput_msg.seqno, 
		temp_imput_msg.data);

	return;
}

/*******************************************************************************
 *                                  Processes                                   *
*******************************************************************************/

PROCESS(sink_process, "Sink process");
AUTOSTART_PROCESSES(&sink_process);

PROCESS_THREAD(sink_process, ev, data)
{
	PROCESS_BEGIN();
	PRINTF("SINK NODE STARTED ...\n");

	SENSORS_ACTIVATE(button_sensor);

	udp_server_start();
	udp_server_add_listener(&udp_app_call);
	PROCESS_PAUSE();

	rpl_router_start();
	PROCESS_PAUSE();
	
	while(1)
	{		
		PROCESS_YIELD();
	}

	PROCESS_END();
}
/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
/** @} */
