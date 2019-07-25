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
	case SIG_LIGHT_ON:
		lightsTime[evn->ledName].isOn = TRUE;
		lightsTime[evn->ledName].begin = xTaskGetTickCount() / portTICK_RATE_MS;
		if (evn->ledName == RED_LED) {
			lightsTime[GREEN_LED].end = xTaskGetTickCount() / portTICK_RATE_MS;
		}
		break;
	case SIG_LIGHT_OFF:
		if (evn->ledName == GREEN_LED) {
			putEvent(statusModule, SIG_LEARNING_WAITING_RED_LIGHT);
		} else if (evn->ledName == RED_LED) {
			putEvent(statusModule, SIG_LEARNING_AGAIN_GREEN_LIGHT_ON);
		}
		break;
	case SIG_LIGHT_GREEN_ON_AGAIN:
		if (evn->ledName == GREEN_LED) {
			lightsTime[RED_LED].end = xTaskGetTickCount() / portTICK_RATE_MS;
			putEvent(statusModule, SIG_LEARNING_FINISH);
		}
	}
}

static void initlightsTimeModule() {
	for (int i = 0; i < MAX_LIGHTS; i++) {
		lightsTime[i].isOn = FALSE;
		lightsTime[i].begin = 0;
		lightsTime[i].end = 0;
	}
}
