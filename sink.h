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
 \addtogroup application
 @{
 */

/**
 * \defgroup   sink Sink Node
 * @{
 * \file       sink.h
 * \authors    Carlos Abreu
 *
 * \brief Sink Node
 */

#include "contiki.h"
#include "dev/button-sensor.h"
#include "udp-server.h"
#include "rpl-router.h"

#ifndef DEBUG
#define DEBUG DEBUG_NONE
   #include "net/ip/uip-debug.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __SINK__
#define __SINK__

/*******************************************************************************
*                                   Defines                                    *
*******************************************************************************/


/*******************************************************************************
*                                   Globals                                    *
*******************************************************************************/


/*******************************************************************************
*                             Function Prototypes                              *
*******************************************************************************/


/*******************************************************************************
*                              Process Prototypes                              *
*******************************************************************************/

PROCESS_NAME(sink_process);

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/
#endif /* __SINK__ */
/** @} */
/** @} */


