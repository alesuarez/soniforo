#ifndef FREERTOS_INC_SONIFORO_H_
#define FREERTOS_INC_SONIFORO_H_
#include "modules.h"
#include "sapi.h"

#define MAX_LIGHTS 2

module_t * statusModule;
module_t * configurationModule;
module_t * learningModule;
module_t * lightsModule;
module_t * lightsTimeModule;
module_t * debounceModule;

typedef struct {
	uint32_t begin;
	uint32_t end;
	bool_t isOn;
} lightTime_t;

static system_general_status_t systemStatus;
static lightTime_t lightsTime[MAX_LIGHTS];



#endif /* FREERTOS_INC_SONIFORO_H_ */
