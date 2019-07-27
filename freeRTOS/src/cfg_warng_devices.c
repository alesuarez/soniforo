#include "cfg_warng_devices.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"

#include "uart.h"
#include "commons.h"
#include "event.h"
#include "soniforo.h"
#include "uart_task.h"

extern module_t * configurationModule;
void sendString(uint8_t * byte, uint8_t legth);
uint8_t * CommandEsp8266ToString[] = {
		"AT\r\n", 										//1
		"AT+RST\r\n", 									//2
		"AT+CWMODE=1\r\n", 								//3
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

static CommandEsp8266_t initVector[COMMAND_INIT_LENGHT] = {
		CMD_AT,
		CMD_RST,
		CMD_CWMODE_1,
		CMD_CIPMUX_1,
		CMD_CIPDINFO_1,
		CMD_CWAUTOCONN_0,
		CMD_CWDHCP_1_1,
	//	CMD_CIPSTATUS_Q,
		CMD_CWMODE_2,
		CMD_CWSAP,
		CMD_CWDHCP_0_1,
		CMD_CIPSTART
};

uint8_t * esp01Responses[] = {
		"OK", //1 ---
		"ready", //2 --
		"OK", //3 --
		"OK", //4
		"OK", //5 --
		"OK", //6 --
		"OK", //7 --
		"3,CONNECT", //8
		"OK", //9
		"OK", //10 --
		"OK", //11 --
		"STATUS:5", //12
		"OK" //13--
		};

uint8_t esp01ResponsesLengh[] = {
		2, //1
		5, //2
		2, //3
		2, //4--
		2, //5
		2, //6
		2, //7
		2, //8
		2, //9
		2, //10
		2, //11
		2, //12
		2 //13
		};



uint8_t * expectedResponse;
uint8_t expectedResponseLegth;
bool_t isResponseOk;

void setExpectedResponse(CommandEsp8266_t cmd) {
	expectedResponse = esp01Responses[cmd];
	expectedResponseLegth = esp01ResponsesLengh[cmd];
}


bool_t sendCmd(CommandEsp8266_t cmd) {
	uint8_t * byte = CommandEsp8266ToString[cmd];

	while (*byte != '\0') {
		xQueueSend(rs232TxQueue, byte, portMAX_DELAY);
		++byte;
	}
	return TRUE;
}

void sendString(uint8_t * byte, uint8_t legth) {

	for(int i = 0; i < legth; i++) {
		xQueueSend(rs232TxQueue, byte, portMAX_DELAY);
		++byte;
	}
}

void esp01ConfigurationTask(void * p) {
	uint8_t attemptsValue = 0;

	for (int i = 0; i < COMMAND_INIT_LENGHT; i++) {
		setExpectedResponse(initVector[i]);

		sendCmd(initVector[i]);

		while(1) {
			if ( xSemaphoreTake( expectedResponseSemaphoreHandle, portMAX_DELAY) == pdTRUE) {
				break;
			}
		}

		if (isResponseOk == FALSE) {
			i = i - 1 < 0 ? 0 : i - 1;
			attemptsValue++;
			if (attemptsValue > MAX_ATTEMPT) {
				gpioWrite( LED1, ON );
				gpioWrite( LED2, ON );
				gpioWrite( LED3, ON );
				break;
			}
		}
	}
	gpioWrite( LEDR, ON );
	putEvent(configurationModule, SIG_CONFIGURING_FINISH);
	vTaskSuspend(esp01ConfigurationTaskHandle); 		// suspendo esta tarea
}

void esp01ExpectedResponseTask(void * p) {
	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	uint8_t byte;
	isResponseOk = FALSE;
	uint8_t counter = 0;
	while (1) {
		if (xQueueReceive(rs232RxQueue, &byte, portMAX_DELAY)) {
			if (*expectedResponse == byte) {
				counter++;
				expectedResponse++;
				if (counter == expectedResponseLegth) {
					isResponseOk = TRUE;
					counter = 0;
					expectedResponse = 0;
					xSemaphoreGive(expectedResponseSemaphoreHandle);
				} else if (counter > expectedResponseLegth) {
					isResponseOk = FALSE;
					xSemaphoreGive(expectedResponseSemaphoreHandle);
				}
			}
			xQueueSend(usbTxQueue, &byte, portMAX_DELAY);
		}
	}
}

void sendStatusCrossToEsp01Task(void * a) {
	portTickType xPeriodicity =  800 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		sendString("Cruzar\r\n",8);
		sendCmd(CMD_CIPSEND);
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity );
	}
}

void sendStatusCautionToEsp01Task(void * a) {
	portTickType xPeriodicity =  800 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		sendString("Apurat\r\n",8);
		sendCmd(CMD_CIPSEND);
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity );
	}
}
