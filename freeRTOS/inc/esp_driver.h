#ifndef FREERTOS_INC_ESP_DRIVER_H_
#define FREERTOS_INC_ESP_DRIVER_H_

#include "commons.h"

#define MAX_COMMAND_LENGHT	 	45
#define COMMAND_INIT_LENGHT	 	12

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

static const char CommandEsp8266ToString[][MAX_COMMAND_LENGHT] = {
		"AT\r\n", //1
		"AT+RST\r\n", //2
		"AT+CWMODE=1\r\n", //3
		"AT+CWMODE=2\r\n", //4
		"AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", //5
		"AT+CWDHCP=0,1\r\n", //6
		"AT+CWDHCP=1,1\r\n", //7
		"AT+CIPSTART=3,\"UDP\",\"0\",0,4096,2\r\n", //8
		"AT+CIPSEND=3,8,\"192.168.4.255\",4096\r\n", //9
		"AT+CIPMUX=1\r\n", //10
		"AT+CIPDINFO=1\r\n", //11
		"AT+CIPSTATUS?\r\n", //12
		"AT+CWAUTOCONN=0\r\n" //13
		};

static char esp01Responses[][MAX_COMMAND_LENGHT] = {
		"AT\r\n", //1
		"AT+RST\r\n", //2
		"CWMODE=1\r\n", //3
		"CWMODE=2\r\n", //4
		"OK\r\n", //5
		"OK\r\n", //6
		"CWDHCP=1,1\r\n", //7
		"3,CONNECT\r\n", //8
		"OK\r\n", //9
		"CIPMUX=1\r\n", //10
		"CIPDINFO=1\r\n", //11
		"STATUS:5\r\n", //12
		"CWAUTOCONN=0\r\n" //13

		};

static CommandEsp8266_t initVector[COMMAND_INIT_LENGHT] = {
		CMD_AT, CMD_RST,
		CMD_CWMODE_1,
		CMD_CIPMUX_1,
		CMD_CIPDINFO_1,
		CMD_CWAUTOCONN_0,
		CMD_CWDHCP_1_1,
		CMD_CIPSTATUS_Q,
		CMD_CWMODE_2,
		CMD_CWSAP,
		CMD_CWDHCP_0_1,
		CMD_CIPSTART
};


bool_t sendCmd(CommandEsp8266_t);

#endif /* FREERTOS_INC_ESP_DRIVER_H_ */