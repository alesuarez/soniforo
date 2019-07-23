#include "cfg_warng_devices.h"
#include "uart.h"
#include "commons.h"
#include "event.h"
#include "soniforo.h"


extern module_t * configurationModule;

char * CommandEsp8266ToString[] = {
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

char * esp01Responses[] = {
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

static CommandEsp8266_t initVector[COMMAND_INIT_LENGHT] = { CMD_AT, CMD_RST,
		CMD_CWMODE_1, CMD_CIPMUX_1, CMD_CIPDINFO_1, CMD_CWAUTOCONN_0,
		CMD_CWDHCP_1_1, CMD_CIPSTATUS_Q, CMD_CWMODE_2, CMD_CWSAP,
		CMD_CWDHCP_0_1, CMD_CIPSTART };


uint8_t sendCmd(CommandEsp8266_t cmd) {
	return sendUart(CommandEsp8266ToString[cmd], esp01Responses[cmd]);
}

void esp01ConfigurationTask(void *p) {
	uint8_t attemptsValue = 0;
	/*for (int i = 0; i < COMMAND_INIT_LENGHT; i++) {
		if (!sendCmd(initVector[i])) {
			vTaskDelay(2000 / portTICK_RATE_MS);
			i = i - 1 < 0 ? 0 : i - 1;

			attemptsValue++;
			if (attemptsValue > MAX_ATTEMPT) {
				gpioWrite( LED1, ON );
				gpioWrite( LED2, ON );
				gpioWrite( LED3, ON );
				break;
			}
		}
		vTaskDelay(5000 / portTICK_RATE_MS);
	}*/
	putEvent(configurationModule, SIG_CONFIGURING_FINISH);
	vTaskSuspend(esp01ConfigurationTaskHandle); 		// suspendo esta tarea
}
