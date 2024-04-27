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
 * \addtogroup rpl-router
 * @{
 * \file       rpl-router.c 
 * \authors    Carlos Abreu
 *
 * \brief A RPL DAG Root
 */

#include "rpl-router.h"

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/


/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/


/*******************************************************************************
*                             		Function     	                       *
*******************************************************************************/

/**
* \fn rpl_router_start(void)
* \brief This function starts the RPL Router process.
* \return void
*
* Example Usage:
* \code
*	rpl_router_start();
* \endcode 
*/  
void rpl_router_start(void)
{
	if (process_is_running(&rpl_router_process)) return;
	process_start(&rpl_router_process, NULL);
}

/**
* \fn rpl_router_stop(void)
* \brief This function stops the RPL Router process.
* \return void
*
* Example Usage:
* \code
*	rpl_router_stop();
* \endcode 
*/  
void rpl_router_stop(void)
{
	if (!process_is_running(&rpl_router_process)) return;
	process_exit(&rpl_router_process);
}

static void create_new_dag(void)
{
	uip_ipaddr_t ipaddr;
	
	uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
	uip_ds6_set_addr_iid(&ipaddr, &uip_lladdr);
	uip_ds6_addr_add(&ipaddr, 0, ADDR_AUTOCONF);

	if(uip_ds6_addr_lookup(&ipaddr) != NULL)
	{
		rpl_dag_t *dag;
		dag = rpl_set_root(RPL_DEFAULT_INSTANCE,(uip_ip6addr_t *)&ipaddr);
		uip_ip6addr(&ipaddr, 0xaaaa, 0, 0, 0, 0, 0, 0, 0);
		rpl_set_prefix(dag, &ipaddr, 64);
		PRINTF("CREATED A NEW DAG ...\n");
	}
	else
	{
		PRINTF("FAILED TO CREATED A NEW DAG!\n");
	}

	return;
}

/*******************************************************************************
*                             		Process		                       *
*******************************************************************************/

PROCESS(rpl_router_process, "RPL Router process");
AUTOSTART_PROCESSES(&rpl_router_process);

PROCESS_THREAD(rpl_router_process, ev, data)
{
	PROCESS_BEGIN();
	PRINTF("RPL ROUTER STARTED ...\n");
	
	create_new_dag();
	PROCESS_PAUSE();

	#ifdef RPL_GLOBAL_REPAIR_PERIOD
		static struct etimer et;
		etimer_set(&et, RPL_GLOBAL_REPAIR_PERIOD);
	#endif
	
	NETSTACK_MAC.off(1);

	while(1)
	{
		PROCESS_YIELD();

		#ifdef RPL_GLOBAL_REPAIR_PERIOD
			// Periodic timer event
			if(etimer_expired(&et))
			{
				etimer_restart(&et);
				printf("Initiaing global repair\n");
		  		rpl_repair_dag(rpl_get_dag(RPL_ANY_INSTANCE));
			}
		#endif
	}

	PROCESS_END();
}

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
/** @} */
