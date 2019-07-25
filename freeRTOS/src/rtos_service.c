#include "rtos_service.h"
#include "callbacks_functions.h"
#include "modules.h"
#include "soniforo.h"
#include "alive_task.h"
#include "init_task.h"
#include "event_queue_task.h"
#include "cfg_warng_devices.h"
#include "send_status_task.h"
#include "debounce_control.h"

static uint32_t getTime(lightTime_t lightsTime);

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
			(const char *) "event_task",
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

	xTaskCreate(sendStatusToEsp01Task,
			(const char *) "sendStatusToEsp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&sendStatusEsp01TaskHandle);
}

void suspendSelectedTasks() {
	vTaskSuspend(ledBlinkingInConfigurationTaskHandle);
	vTaskSuspend(esp01ConfigurationTaskHandle);
	vTaskSuspend(sendStatusEsp01TaskHandle);
	vTaskSuspend(initTaskHandle);
}

void initQueues( void ) {
	eventQueue = xQueueCreate(16, sizeof( event_t));
}

void createTimers( void ) {
	redLightTimerHandle = xTimerCreate("Timer red light", getTime(lightsTime[RED_LED]), pdFALSE, 0, redLightCallback);
	//lightsTimeArray[1] = xTimerCreate("Timer yellow light", DEBOUNCE_FILTER_TIMER_PERIOD, pdFALSE, 0, yellowLightCallback);
	greenLightTimerHandle = xTimerCreate("Timer green light", getTime(lightsTime[GREEN_LED]), pdFALSE, 0, greenLightCallback);
}

void createInitConfigurationTimer(void) {
	initConfigurationTimerHandle = xTimerCreate("Timer for init configuration", pdMS_TO_TICKS( 5000 ), pdFALSE, 0, initConfigurationCallback);
	xTimerStart(initConfigurationTimerHandle, 0);
}

void createLightDebounceTimers(void) {
	lightDebounceTimerHandles[RED_LED] = xTimerCreate("Timer for red light", DEBOUNCE_FILTER_TIMER_PERIOD, pdFALSE, ( void * ) 0, debounceRedLightCallback);
	lightDebounceTimerHandles[YELLOW_LED] = xTimerCreate("Timer for yellow light", DEBOUNCE_FILTER_TIMER_PERIOD, pdFALSE, ( void * ) 0, debounceYellowLightCallback);
	lightDebounceTimerHandles[GREEN_LED] = xTimerCreate("Timer for green light", DEBOUNCE_FILTER_TIMER_PERIOD, pdFALSE, ( void * ) 0, debounceGreenLightCallback);
}

static uint32_t getTime(lightTime_t lightsTime) {
	return lightsTime.end - lightsTime.begin;
}
