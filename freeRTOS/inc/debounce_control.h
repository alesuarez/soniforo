#ifndef FREERTOS_INC_DEBOUNCE_CONTROL_H_
#define FREERTOS_INC_DEBOUNCE_CONTROL_H_
#include "event_framework.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timers.h"

TimerHandle_t lightDebounceTimerHandles[4];

void debounceHandler(event_t * evn);

#endif /* FREERTOS_INC_DEBOUNCE_CONTROL_H_ */
