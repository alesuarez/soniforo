#include "alive_task.h"

void aliveTask(void * a) {
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
	 gpioToggle(LED3);
	 vTaskDelayUntil(&xLastWakeTime, xPeriodicity );
	}
}
