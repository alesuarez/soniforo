#include "warng_devices.h"

void sendStatusToEsp01Task(void * a) {
	portTickType xPeriodicity =  800 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		debugPrintlnString("Cruzar\r\n");
		sendCmd(CMD_CIPSEND);
		vTaskDelay(20 / portTICK_RATE_MS);
		consolePrintString("Cruzar\r\n");
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity );
	}
}


