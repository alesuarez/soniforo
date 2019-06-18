#include "commons.h"
#include "rtos_driver.h"

int main(void) {

	boardConfig();

	IRQ_init();							// configuro las interrupciones

	debugPrintConfigUart( UART_USB, DEFAULT_BAUD_RATE );
	debugPrintlnString("Inicio de programa... \r\n");

	sendBuffer = xQueueCreate(10, sizeof(Message));
	uartQueue = xQueueCreate(10, sizeof(char *));
	// Crear tarea en freeRTOS
	tasks_init();

	vTaskSuspend(sendStatusToEthernetHandle);

	vTaskSuspend(ligthRedTaskHandle);
	vTaskSuspend(ligthYellowTaskHandle);
	vTaskSuspend(ligthGreenTaskHandle);

	vTaskStartScheduler();

	while ( TRUE) {
		gpioWrite(LED1, ON);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, ON);
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}

	return 0;
}
