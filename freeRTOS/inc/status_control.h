#ifndef FREERTOS_INC_STATUS_CONTROL_H_
#define FREERTOS_INC_STATUS_CONTROL_H_
#include "commons.h"
#include "event_framework.h"

void statusHandler(event_t *);
system_general_status_t getGeneralSystemStatus();

#endif /* FREERTOS_INC_STATUS_CONTROL_H_ */
