#ifndef FREERTOS_INC_EVENT_H_
#define FREERTOS_INC_EVENT_H_

#include "event_framework.h"
#include "commons.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

void putEvent(module_t *, signal_t);
void putLightEvent(module_t *, signal_t, led_name_t);
portBASE_TYPE putEventFromISR(module_t *, signal_t, led_name_t);
void resendEvent (module_t *, event_t *);

#endif /* FREERTOS_INC_EVENT_H_ */
