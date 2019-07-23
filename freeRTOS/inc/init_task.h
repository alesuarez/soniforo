#ifndef FREERTOS_INC_INIT_TASK_H_
#define FREERTOS_INC_INIT_TASK_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

TaskHandle_t initTaskHandle;

void initTask(void *);

#endif /* FREERTOS_INC_INIT_TASK_H_ */
