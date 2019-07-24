#include "alive_task.h"
#include "sapi.h"

void aliveTask(void * a) {
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	while (1) {
		gpioToggle(LEDB);
		vTaskDelay(xPeriodicity);
	}
}

void ledBlinkingInConfigurationTask(void * a) {
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	while (1) {
		gpioToggle(LEDG);
		vTaskDelay(xPeriodicity);
	}
}
