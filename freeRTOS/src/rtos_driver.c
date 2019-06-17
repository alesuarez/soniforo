#include "rtos_driver.h"
#include "alive_task.h"
#include "ligth_red_task.h"
#include "ligth_yellow_task.h"
#include "ligth_green_task.h"
#include "receive_queue_task.h"
#include "cfg_warng_devices.h"
#include "warng_devices.h"


void tasks_init() {
	xTaskCreate(ligthRedTask, (const char *) "ligthRedTask",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 7,
			&ligthRedTaskHandle);

	xTaskCreate(ligthYellowTask, (const char *) "ligthYellowTask",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 7,
			&ligthYellowTaskHandle);

	xTaskCreate(ligthGreenTask, (const char *) "ligthGreenTask",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 7,
			&ligthGreenTaskHandle);

	xTaskCreate(receiveQueueTask, (const char *) "send",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 1,
			&sendTaskHandle);

	xTaskCreate(sendStatusToEsp01Task, (const char *) "sendStatusToEthernet",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 1,
			&sendStatusToEthernetHandle);

	xTaskCreate(esp01Task, (const char *) "esp01Task",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 1,
			&esp01TaskHandle);

	xTaskCreate(aliveTask, (const char *) "aliveTask",
			configMINIMAL_STACK_SIZE * 2, &sendBuffer, tskIDLE_PRIORITY + 1,
			&blinkLedConfigurationTaskHandle);
}

void semaphore_init() {
	xsRedLightOff = xSemaphoreCreateBinary();
	xsRedLigthOn = xSemaphoreCreateBinary();

	xsYellowLightOff = xSemaphoreCreateBinary();
	xsYellowLigthOn = xSemaphoreCreateBinary();

	xsGreenLightOff = xSemaphoreCreateBinary();
	xsGreenLigthOn = xSemaphoreCreateBinary();
}
