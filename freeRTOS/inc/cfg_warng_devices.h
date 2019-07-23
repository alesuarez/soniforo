#ifndef FREERTOS_INC_CFG_WARNG_DEVICES_H_
#define FREERTOS_INC_CFG_WARNG_DEVICES_H_

#include "sapi.h"

#define MAX_COMMAND_LENGHT	 	45
#define COMMAND_INIT_LENGHT	 	12
#define MAX_ATTEMPT				3

typedef enum CommandEsp8266 {
	CMD_AT, //1
	CMD_RST, //2
	CMD_CWMODE_1, //3
	CMD_CWMODE_2, //4
	CMD_CWSAP, //5
	CMD_CWDHCP_0_1, //6
	CMD_CWDHCP_1_1, //7
	CMD_CIPSTART, //8
	CMD_CIPSEND, //9
	CMD_CIPMUX_1, //10
	CMD_CIPDINFO_1, //11
	CMD_CIPSTATUS_Q, //12
	CMD_CWAUTOCONN_0 //13
} CommandEsp8266_t;

void esp01Task(void *);
uint8_t sendCmd(CommandEsp8266_t) ;

#endif /* FREERTOS_INC_CFG_WARNG_DEVICES_H_ */
