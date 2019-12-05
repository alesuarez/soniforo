#include "rtos_service.h"
#include "semphr.h"
#include "callbacks_functions.h"
#include "modules.h"
#include "soniforo.h"
#include "alive_task.h"
#include "init_task.h"
#include "event_queue_task.h"
#include "uart_task.h"
#include "sonometer_task.h"
#include "cfg_warng_devices.h"
#include "debounce_control.h"

static uint32_t getTime(lightTime_t lightTime);

void createAllTasks() {

	xTaskCreate(aliveTask,
			(const char *) "aliveTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

	xTaskCreate(initTask,
			(const char *) "initTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&initTaskHandle);

	xTaskCreate(eventQueueTask,
			(const char *) "eventQueueTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

	xTaskCreate(usbRxTask,
			(const char *) "usbRxTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

	xTaskCreate(usbTxTask,
			(const char *) "usbTxTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);
	xTaskCreate(rs232RxTask,
			(const char *) "rs232RxTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

		xTaskCreate(rs232TxTask,
			(const char *) "rs232RxTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

	xTaskCreate(ledBlinkingInConfigurationTask,
			(const char *) "ledBlinkingInConfigurationTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&ledBlinkingInConfigurationTaskHandle);

	xTaskCreate(esp01ConfigurationTask,
			(const char *) "esp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&esp01ConfigurationTaskHandle);

	xTaskCreate(sendStatusCrossToEsp01Task,
			(const char *) "sendStatusToEsp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&sendStatusCrossEsp01TaskHandle);

	xTaskCreate(sendStatusCautionToEsp01Task,
			(const char *) "sendStatusToEsp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&sendStatusCautionEsp01TaskHandle);

	xTaskCreate(esp01ExpectedResponseTask,
			(const char *) "esp01ExpectedResponseTask",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			0);

	xTaskCreate(sonomterTask,
				(const char *) "sonomterTask",
				configMINIMAL_STACK_SIZE * 2,
				NULL,
				tskIDLE_PRIORITY + 1,
				0);


}

void suspendSelectedTasks() {
	vTaskSuspend(ledBlinkingInConfigurationTaskHandle);
	vTaskSuspend(esp01ConfigurationTaskHandle);
	vTaskSuspend(sendStatusCrossEsp01TaskHandle);
	vTaskSuspend(sendStatusCautionEsp01TaskHandle);
	vTaskSuspend(initTaskHandle);
}

void initQueues( void ) {
	eventQueue = xQueueCreate(80, sizeof( event_t));
	usbRxQueue = xQueueCreate(80, sizeof( uint8_t));
	usbTxQueue = xQueueCreate(80, sizeof( uint8_t));
	rs232RxQueue = xQueueCreate(80, sizeof( uint8_t));
	rs232TxQueue = xQueueCreate(80, sizeof( uint8_t));
}

void initSemaphores() {
	expectedResponseSemaphoreHandle = xSemaphoreCreateBinary();
}

void createLightAdvertisementTimers( void ) {

	uint32_t originalRedTime = getTime(lightsTime[RED_LED]);
	uint32_t redTime = originalRedTime * 0.65;
	uint32_t yellowTime = originalRedTime * 0.35;
	uint32_t greenTime = getTime(lightsTime[GREEN_LED]);

	redLightTimerHandle = xTimerCreate("Timer red light",   pdMS_TO_TICKS(redTime), pdFALSE, 0, redLightCallback);
	yellowLightTimerHandle = xTimerCreate("Timer yellow light",  pdMS_TO_TICKS(yellowTime), pdFALSE, 0, yellowLightCallback);
	//greenLightTimerHandle = xTimerCreate("Timer green light",  pdMS_TO_TICKS(greenTime), pdFALSE, 0, greenLightCallback);
}

void createInitConfigurationTimer(void) {
	initConfigurationTimerHandle = xTimerCreate("Timer for init configuration", pdMS_TO_TICKS( 5000 ), pdFALSE, 0, initConfigurationCallback);
	xTimerStart(initConfigurationTimerHandle, 0);
}

void createLightDebounceTimers(void) {
	//lightDebounceTimerHandles[RED_LED] = xTimerCreate("Timer for red light", pdMS_TO_TICKS( 100 ), pdFALSE, ( void * ) 0, debounceRedLightCallback);
	//lightDebounceTimerHandles[YELLOW_LED] = xTimerCreate("Timer for yellow light", pdMS_TO_TICKS( 100 ), pdFALSE, ( void * ) 0, debounceYellowLightCallback);
	//lightDebounceTimerHandles[GREEN_LED] = xTimerCreate("Timer for green light", pdMS_TO_TICKS( 100 ), pdFALSE, ( void * ) 0, debounceGreenLightCallback);
}

static uint32_t getTime(lightTime_t lightTime) {
	return lightTime.end - lightTime.begin;
}
