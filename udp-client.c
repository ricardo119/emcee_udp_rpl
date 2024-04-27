/*
 * Copyright (c) 2020, Instituto Politécnico de Viana do Castelo - Portugal (IPVC).
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE UM AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE UM OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/**
 *
 * \addtogroup udp-client
 * @{
 * \file       udp-client.c 
 * \authors    Carlos Abreu
 *
 * \brief A simple IPv6 UDP Client.
 */

#include "udp-client.h"

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/

/*******************************************************************************
*                               Global Variables                               *
*******************************************************************************/

static struct uip_udp_conn *conn;
static uip_ipaddr_t server_ipaddr;
static char databuffer[UIP_BUFSIZE];

static void (*listeners_list[MAX_LISTENERS]) (char *data, uip_ipaddr_t* srcipaddr);

/*******************************************************************************
*                                  Functions                                   *
*******************************************************************************/

/**
* \fn udp_client_add_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr))
* \brief Add listener to call on new data.
* \return The listener ID or ZERO if the list is full.
*
* Example Usage:
* \code
*	udp_client_add_listener(&udp_app_call);
* \endcode 
*/ 
uint8_t udp_client_add_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr))
{
	int i;
	for(i = 0; i < MAX_LISTENERS; i++)
	{
		if(listeners_list[i] == NULL)
		{
			listeners_list[i] = fp;
			return i;
		}
	}

	return 0;
}

/**
* \fn udp_client_remove_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr))
* \brief Remove listener.
* \return The listener ID
*
* Example Usage:
* \code
*	udp_client_remove_listener(&udp_app_call);
* \endcode 
*/ 
uint8_t udp_client_remove_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr))
{
	int i;
	for(i = 0; i < MAX_LISTENERS; i++)
	{
		if(listeners_list[i] == fp)
		{
			listeners_list[i] = NULL;
			return i;
		}
	}

	return 0;
}

static void udp_client_remove_listeners(void)
{
	// Clean the listeners list. Setting the list to NULL
	memset(&listeners_list , '\0', sizeof(listeners_list));
	return;
}

/**
* \fn udp_client_start(void)
* \brief This function starts the UDP Client process.
* \return void
*
* Example Usage:
* \code
*	udp_client_start();
* \endcode 
*/  
void udp_client_start(void)
{
	if (process_is_running(&udp_client_process)) return;
	process_start(&udp_client_process, NULL);
}

/**
* \fn udp_client_stop(void)
* \brief This function stops the UDP Client process.
* \return void
*
* Example Usage:
* \code
*	udp_client_stop();
* \endcode 
*/  
void udp_client_stop(void)
{
	if (!process_is_running(&udp_client_process)) return;
	process_exit(&udp_client_process);
}

/**
* \fn udp_send(char* buf, uint8_t len)
* \brief Send a UDP packet
* \param buf A pointer to the data to be sent
* \return void
*
* Example Usage:
* \code
*	udp_send(buf, len);
* \endcode 
*/ 
void udp_send(char* buf, uint8_t len)
{
   //if (conn == NULL) return;
	if (conn == NULL || len <= 0) return;

	uip_udp_packet_sendto(conn, buf, len, &conn->ripaddr, 
	                        UIP_HTONS(UDP_SERVER_PORT));

	//PRINTF("UDP Client Sent MSG!\n");
	//PRINTF("Sent to: "); PRINT6ADDR(&conn->ripaddr); PRINTF("\n");

	return;
}

static void tcpip_handler(void)
{	
	if(uip_newdata())
	{
		memset(databuffer, '\0', sizeof(databuffer));
		memcpy(databuffer, uip_appdata, uip_datalen());
		databuffer[uip_datalen()] = '\0';

		//memcpy(&msg, databuffer, sizeof(msg));
		//PRINTF("R: Seq %lu ", msg.seqno); PRINT6ADDR(&UIP_IP_BUF->srcipaddr); PRINTF("\n");
		
		// Send data to application.
		int i;
		for(i = 0; i < MAX_LISTENERS; i++)
		{
			if(listeners_list[i] != NULL)
			{
				listeners_list[i]((char *)databuffer, &UIP_IP_BUF->srcipaddr);
			}
		}
	}

	return;
}

static void set_global_address(void)
{
	uip_ipaddr_t ipaddr;

	uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
	uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
	uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

	SERVER_IP_ADDR(&server_ipaddr);

	return;
}

static void create_conn(void)
{
	conn = udp_new(&server_ipaddr, UIP_HTONS(UDP_SERVER_PORT), NULL);
	udp_bind(conn, UIP_HTONS(UDP_CLIENT_PORT));
   
	PRINTF("Created a connection with the server ");
	PRINT6ADDR(&conn->ripaddr);
	PRINTF(" local/remote port %u/%u\n", 
		 UIP_HTONS(conn->lport), UIP_HTONS(conn->rport));

	return;
}

static void reset()
{
	udp_client_remove_listeners();

	return;
}

/*******************************************************************************
*                                  Processes                                   *
*******************************************************************************/

PROCESS(udp_client_process, "UDP client process");
AUTOSTART_PROCESSES(&udp_client_process);

/**
* \brief  A simple IPv6 UDP Client.
*/
PROCESS_THREAD(udp_client_process, ev, data)
{
	PROCESS_BEGIN();
	PRINTF("UDP CLIENT STARTED ...\n");

	reset();

	set_global_address();
	PROCESS_PAUSE();

	create_conn();
	PROCESS_PAUSE();
	
	while(1)
	{
		PROCESS_YIELD();

		if(ev == tcpip_event)
		{
			tcpip_handler();
		}
	}

	PROCESS_END();
}
/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
/** @} */
