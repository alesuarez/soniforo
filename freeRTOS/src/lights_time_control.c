#include "lights_time_control.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "soniforo.h"
#include "event.h"

extern module_t * statusModule;

static void initlightsTimeModule();

void lightsTimeHandler(event_t * evn) {
	switch (evn->signal) {
	case SIG_INIT:
		initlightsTimeModule();
		break;
	case SIG_LIGHT_ON:
		lightsTime[evn->ledName].isOn = TRUE;
		lightsTime[evn->ledName].begin = xTaskGetTickCount() / portTICK_RATE_MS;
		break;
	case SIG_LIGHT_OFF:
		lightsTime[evn->ledName].isOn = FALSE;
		lightsTime[evn->ledName].begin = xTaskGetTickCount() / portTICK_RATE_MS;
		if (evn->ledName == GREEN_LED) {
			putEvent(statusModule, SIG_LEARNING_WAITING_RED_LIGHT);
		} else if (evn->ledName == RED_LED) {
			putEvent(statusModule, SIG_LEARNING_FINISH);
		}
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
