#include "lights_time_control.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "soniforo.h"
#include "event.h"

static void initlightsTimeModule();

void lightsTimeHandler(event_t * evn) {
	switch (evn->signal) {
	case SIG_INIT:
		initlightsTimeModule();
		break;
	case SIG_LIGHT_GREEN_ON:
		lightsTime[GREEN_LED].isOn = TRUE;
		lightsTime[GREEN_LED].begin = xTaskGetTickCount();
		break;
	case SIG_LIGHT_RED_ON:
		lightsTime[GREEN_LED].isOn = FALSE;
		lightsTime[GREEN_LED].end = xTaskGetTickCount();
		lightsTime[RED_LED].isOn = TRUE;
		lightsTime[RED_LED].begin = xTaskGetTickCount();
		break;
	case SIG_LIGHT_GREEN_ON_AGAIN:
			lightsTime[RED_LED].end = xTaskGetTickCount();
		break;
	}
}

static void initlightsTimeModule() {
	for (int i = 0; i < MAX_LIGHTS; i++) {
		lightsTime[i].isOn = FALSE;
		lightsTime[i].begin = 0;
		lightsTime[i].end = 0;
	}
}
