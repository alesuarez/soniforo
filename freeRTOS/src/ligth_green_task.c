#include "ligth_green_task.h"


extern SemaphoreHandle_t xsGreenLigthOn;
extern SemaphoreHandle_t xsGreenLightOff;

Message processLigthGreen(Message ligthGreenTaskMessage, xQueueHandle buffer) {
	if ( xSemaphoreTake( xsGreenLigthOn, portMAX_DELAY) == pdTRUE) { // si detecto bajo - alto
		if (isHigh(GREEN_LED_PORT)) {
			ligthGreenTaskMessage.Led = GREEN_LED;
			ligthGreenTaskMessage.Status = LED_ON;
			xQueueSend(buffer, &ligthGreenTaskMessage, portMAX_DELAY);
		}
	}

	if ( xSemaphoreTake( xsGreenLightOff, portMAX_DELAY) == pdTRUE) { // si detecto alto - bajo
		if (!isHigh(GREEN_LED_PORT)) {
			ligthGreenTaskMessage.Led = GREEN_LED;
			ligthGreenTaskMessage.Status = LED_OFF;
			xQueueSend(buffer, &ligthGreenTaskMessage, portMAX_DELAY);
		}
	}
	return ligthGreenTaskMessage;
}

void ligthGreenTask(void *p) {
	xQueueHandle buffer = *(xQueueHandle *) p;
	Message ligthGreenTaskMessage;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		processLigthGreen(ligthGreenTaskMessage, buffer);
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}
