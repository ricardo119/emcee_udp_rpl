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
 * \defgroup   udp-server UDP Server
 * @{
 * \file       udp-server.h
 * \authors    Carlos Abreu
 *
 * \brief A simple IPv6 UDP Server.
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#ifndef DEBUG
#define DEBUG DEBUG_PRINT
   #include "net/ip/uip-debug.h"
#endif

#include "udp-conf.h"

#ifndef __UDP_SERVER__
#define __UDP_SERVER__

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/

#ifdef CONF_MAX_LISTENERS
	#define MAX_LISTENERS   CONF_MAX_LISTENERS
#else
	#define MAX_LISTENERS   5
#endif

/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/


/*******************************************************************************
*                             Function Prototypes                              *
*******************************************************************************/

void udp_server_start(void);
void udp_server_stop(void);

void udp_server_send(char* buf, uint8_t len, uip_ipaddr_t* destipaddr);

uint8_t udp_server_add_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr));
uint8_t udp_server_remove_listener(void (*fp) (char *data, uip_ipaddr_t* srcipaddr));

/*******************************************************************************
*                             Process Prototypes                               *
*******************************************************************************/

PROCESS_NAME(udp_server_process);

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
#endif /* __UDP_SERVER__ */
/** @} */
/** @} */


