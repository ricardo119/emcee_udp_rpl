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
 \addtogroup transport
 @{
 */

/**
 *
 * \defgroup   udp-client UDP Client
 * @{
 * \file       udp-client.h
 *             A simple IPv6 UDP Client.
 * \authors    Carlos Abreu
 *
 * \brief 
 * A simple IPv6 UDP Client.
 */

#include <stdio.h>
#include <string.h>

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include "udp-conf.h"

#ifndef DEBUG
#define DEBUG DEBUG_PRINT
   #include "net/ip/uip-debug.h"
#endif

#ifndef __UDP_CLIENT__
#define __UDP_CLIENT__ 

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/

#ifdef CONF_MAX_LISTENERS
	#define MAX_LISTENERS   CONF_MAX_LISTENERS
#else
	#define MAX_LISTENERS   5
#endif

#define UIP_IP_BUF   ((struct uip_ip_hdr *)&uip_buf[UIP_LLH_LEN])

/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/


/*******************************************************************************
*                             Function Prototypes                              *
*******************************************************************************/

void udp_client_start(void);
void udp_client_stop(void);

void udp_send(char* buf, uint8_t len);

uint8_t udp_client_add_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr));
uint8_t udp_client_remove_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr));

/*******************************************************************************
*                              Process Prototypes                              *
*******************************************************************************/

PROCESS_NAME(udp_client_process);

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
#endif /* __UDP_CLIENT__ */
/** @} */
/** @} */


