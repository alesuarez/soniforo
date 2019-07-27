#include "uart_task.h"
#include "task.h"
#include "sapi.h"

void usbRxTask(void * p) {
	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	uint8_t byte;
	while (1) {
		if (xQueueReceive(usbRxQueue, &byte, portMAX_DELAY)) {
			xQueueSend(rs232TxQueue, &byte, portMAX_DELAY);
		}
	}
}

void usbTxTask(void * p) {
	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	uint8_t byte;
	while (1) {
		if (xQueueReceive(usbTxQueue, &byte, portMAX_DELAY)) {
			uartWriteByte(UART_USB, byte);
		}
	}
}

void rs232RxTask(void * p) {
	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	uint8_t byte;
	while (1) {
	//	if (xQueueReceive(rs232RxQueue, &byte, portMAX_DELAY)) {
		//	xQueueSend(usbTxQueue, &byte, portMAX_DELAY);
		//}
	}
}

void rs232TxTask(void * p) {
	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	uint8_t byte;
	while (1) {
		if (xQueueReceive(rs232TxQueue, &byte, portMAX_DELAY)) {
			uartWriteByte(UART_232, byte);
		}
	}
}
