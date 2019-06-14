#include "ligth_red_task.h"

void ligthRedTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthRedTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	while (1) {

		if ( xSemaphoreTake( xsRedLigthOn, portMAX_DELAY) == pdTRUE) { // si detecto bajo - alto
			if (isHigh(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;
				ligthRedTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsRedLightOff, portMAX_DELAY) == pdTRUE) { // si detecto alto - bajo
			if (!isHigh(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;						// para esta version no se tuvo en cuenta el estado
				ligthRedTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}
