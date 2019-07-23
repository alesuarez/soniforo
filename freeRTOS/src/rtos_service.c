#include "rtos_service.h"
#include "modules.h"
#include "soniforo.h"
#include "alive_task.h"
#include "init_task.h"
#include "event_queue_task.h"
#include "cfg_warng_devices.h"
#include "send_status_task.h"

static void redLightCallback();
static void greenLightCallback();
static uint32_t getTime(lightTime_t lightsTime);

void create_all_tasks() {

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
			&configurationTaskHandle);

	xTaskCreate(esp01Task,
			(const char *) "esp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&esp01TaskHandle);

	xTaskCreate(sendStatusToEsp01Task,
			(const char *) "sendStatusToEsp01Task",
			configMINIMAL_STACK_SIZE * 2,
			NULL,
			tskIDLE_PRIORITY + 1,
			&sendStatusTaskHandle);
}

void suspend_selected_tasks() {
	vTaskSuspend(configurationTaskHandle);
	vTaskSuspend(esp01TaskHandle);
	vTaskSuspend(sendStatusTaskHandle);
	vTaskSuspend(initTaskHandle);
}

void init_queues( void ) {
	eventQueue = xQueueCreate(16, sizeof( event_t));
}

void create_timers( void ) {
	redLightTimerHandle = xTimerCreate("Timer red light", getTime(lightsTime[RED_LED]), pdFALSE, 0, redLightCallback);
	//lightsTimeArray[1] = xTimerCreate("Timer yellow light", DEBOUNCE_FILTER_TIMER_PERIOD, pdFALSE, 0, yellowLightCallback);
	greenLightTimerHandle = xTimerCreate("Timer green light", getTime(lightsTime[GREEN_LED]), pdFALSE, 0, greenLightCallback);
}



static uint32_t getTime(lightTime_t lightsTime) {
	return lightsTime.end - lightsTime.begin;
}

static void redLightCallback() {

}

static void greenLightCallback() {

}


