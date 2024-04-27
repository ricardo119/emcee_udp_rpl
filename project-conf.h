/*******************************************************************************
*                                 Application                                  *
*******************************************************************************/

#define CONF_SETUP_INTERVAL CLOCK_SECOND*5
#define CONF_SEND_INTERVAL CLOCK_SECOND*1
#define CONF_TEMP_READINGS CLOCK_SECOND *10

/*******************************************************************************
*                                     UIP                                      *
*******************************************************************************/

//#define QUEUEBUF_CONF_NUM		8
//#define UIP_CONF_BUFFER_SIZE	140

/*******************************************************************************
*                                     RPL                                      *
*******************************************************************************/

//#define RPL_CONF_OF rpl_mrhof
#define RPL_CONF_OF rpl_of_0

// RPL_CONF_DIO_INTERVAL_MIN 12 ~= 4s
// RPL_CONF_DIO_INTERVAL_MIN 16 ~= 65s
#define RPL_CONF_DIO_INTERVAL_MIN 16

// RPL_CONF_DIO_INTERVAL_DOUBLINGS 4 ~= 1 minuto
// RPL_CONF_DIO_INTERVAL_DOUBLINGS 6 ~= 4 minutos
// RPL_CONF_DIO_INTERVAL_DOUBLINGS 8 ~= 17 minutos
// RPL_CONF_DIO_INTERVAL_DOUBLINGS 10 ~= 70 minutos
#define RPL_CONF_DIO_INTERVAL_DOUBLINGS 10

/*******************************************************************************
*                                     MAC                                      *
*******************************************************************************/

//#define CSMA_CONF_MAX_MAC_TRANSMISSIONS 1

#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 32
//#define NETSTACK_CONF_RDC_CHANNEL_CHECK_RATE 8
#define NETSTACK_CONF_RDC nullrdc_driver
//#define NETSTACK_CONF_RDC contikimac_driver

/*******************************************************************************
*                                   Radio                                      *
*******************************************************************************/

// Current consumption on the radio receiving 19.7 mA.
// The current comsumption of the radio transmission depends on the tx power used.
#define RADIO_TX_POWER_0dBm  31 //   0 dbm 17.4 mA
#define RADIO_TX_POWER_1dBm  27 //  -1 dbm 16.5 mA
#define RADIO_TX_POWER_3dBm  23 //  -3 dbm 15.2 mA
#define RADIO_TX_POWER_5dBm  19 //  -5 dbm 13.9 mA
#define RADIO_TX_POWER_7dBm  15 //  -7 dbm 12.5 mA
#define RADIO_TX_POWER_10dBm 11 // -10 dbm 11.2 mA
#define RADIO_TX_POWER_15dBm  7 // -15 dbm  9.9 mA
#define RADIO_TX_POWER_25dBm  3 // -25 dbm  8.5 mA

#define CONF_CC2420_TX_POWER RADIO_TX_POWER_10dBm

#define CC2420_CONF_CHANNEL 15
//#define CC2420_CONF_CHANNEL 26

/*******************************************************************************
*                                 RPL Repair                                   *
*******************************************************************************/

//#define RPL_GLOBAL_REPAIR_PERIOD CLOCK_SECOND * 60 * 1

/*******************************************************************************
*                                     End                                      *
*******************************************************************************/

