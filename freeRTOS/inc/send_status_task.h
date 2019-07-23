#ifndef FREERTOS_INC_SEND_STATUS_TASK_H_
#define FREERTOS_INC_SEND_STATUS_TASK_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"

TaskHandle_t sendStatusEsp01TaskHandle;

void sendStatusToEsp01Task(void *);

#endif /* FREERTOS_INC_SEND_STATUS_TASK_H_ */
