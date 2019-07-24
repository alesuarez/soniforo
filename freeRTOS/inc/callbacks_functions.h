#ifndef FREERTOS_INC_CALLBACKS_FUNCTIONS_H_
#define FREERTOS_INC_CALLBACKS_FUNCTIONS_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timers.h"

void initConfigurationCallback();

void redLightCallback();
void yellowLightCallback();
void greenLightCallback();

void debounceRedLightCallback(TimerHandle_t);
void debounceYellowLightCallback(TimerHandle_t);
void debounceGreenLightCallback(TimerHandle_t);

#endif /* FREERTOS_INC_CALLBACKS_FUNCTIONS_H_ */
