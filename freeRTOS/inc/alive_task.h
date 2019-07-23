#ifndef FREERTOS_INC_ALIVE_TASK_H_
#define FREERTOS_INC_ALIVE_TASK_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

TaskHandle_t aliveTaskHandle;
TaskHandle_t ledBlinkingInConfigurationTaskHandle;

void aliveTask(void *);
void ledBlinkingInConfigurationTask(void *);

#endif /* FREERTOS_INC_ALIVE_TASK_H_ */
