#include "alive_task.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "sapi.h"

void aliveTask(void * a) {
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	//debugPrintConfigUart( UART_USB, DEFAULT_BAUD_RATE );
	while (1) {
		//debugPrintlnString( "Sistema vivo" );
		gpioToggle(LED3);
		vTaskDelay( xPeriodicity);
	}
}

void ledBlinkingInConfigurationTask(void * a) {
	portTickType xPeriodicity =  500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	//debugPrintConfigUart( UART_USB, DEFAULT_BAUD_RATE );
	while (1) {
		//debugPrintlnString( "Sistema en modo configuracion..." );
		gpioToggle(LED1);
		vTaskDelay( xPeriodicity);
	}
}
