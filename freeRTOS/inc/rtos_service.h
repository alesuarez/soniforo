#ifndef FREERTOS_INC_RTOS_SERVICE_H_
#define FREERTOS_INC_RTOS_SERVICE_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "timers.h"

QueueHandle_t eventQueue;

//Timers
TimerHandle_t redLightTimerHandle;
TimerHandle_t greenLightTimerHandle;

TaskHandle_t esp01TaskHandle;
TaskHandle_t aliveTaskHandle;
TaskHandle_t configurationTaskHandle;
TaskHandle_t sendStatusTaskHandle;


void create_all_tasks();
void suspend_selected_tasks();

void init_queues(void);
void create_timers(void);

#endif /* FREERTOS_INC_RTOS_SERVICE_H_ */
