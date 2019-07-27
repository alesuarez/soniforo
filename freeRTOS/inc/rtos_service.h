#ifndef FREERTOS_INC_RTOS_SERVICE_H_
#define FREERTOS_INC_RTOS_SERVICE_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "timers.h"

QueueHandle_t eventQueue;


TimerHandle_t redLightTimerHandle;
TimerHandle_t yellowLightTimerHandle;
TimerHandle_t greenLightTimerHandle;

TimerHandle_t initConfigurationTimerHandle;

void createAllTasks();
void suspendSelectedTasks();

void initQueues(void);
void createLightAdvertisementTimers(void);
void createInitConfigurationTimer(void);
void createLightDebounceTimers(void);

#endif /* FREERTOS_INC_RTOS_SERVICE_H_ */
