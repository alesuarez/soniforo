#ifndef FREERTOS_INC_RTOS_DRIVER_H_
#define FREERTOS_INC_RTOS_DRIVER_H_

#ifdef TEST
#include "FreeRtos_test.h"

#else
#include "commons.h"
#endif


SemaphoreHandle_t xsRedLightOff;
SemaphoreHandle_t xsRedLigthOn;

SemaphoreHandle_t xsYellowLightOff;
SemaphoreHandle_t xsYellowLigthOn;

SemaphoreHandle_t xsGreenLightOff;
SemaphoreHandle_t xsGreenLigthOn;

TaskHandle_t sendStatusToEthernetHandle;
TaskHandle_t ligthYellowTaskHandle;
TaskHandle_t ligthGreenTaskHandle;
TaskHandle_t ligthRedTaskHandle;
TaskHandle_t sendTaskHandle;
TaskHandle_t esp01TaskHandle;
TaskHandle_t blinkLedConfigurationTaskHandle;

void tasks_init();
void semaphore_init();

#endif /* FREERTOS_INC_RTOS_DRIVER_H_ */
