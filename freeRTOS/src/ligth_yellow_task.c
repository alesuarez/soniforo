#include "ligth_yellow_task.h"

void ligthYellowTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	Message ligthYellowTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsYellowLigthOn, portMAX_DELAY) == pdTRUE) { 	// si detecto bajo - alto
			if (isHigh(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;
				ligthYellowTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsYellowLightOff, portMAX_DELAY) == pdTRUE) { 	// si detecto alto - bajo
			if (!isHigh(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;					// para esta version no se tuvo en cuenta el estado
				ligthYellowTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}
