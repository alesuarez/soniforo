#include "lights_control.h"
#include "status_control.h"
#include "event.h"
#include "soniforo.h"

static void processLightOn(event_t * evn);
static void processLightOff(event_t * evn);
static void processLightOnRunning(event_t * evn);
static void processLightOffRunning(event_t * evn);

void lightsHandler(event_t * evn) {
	switch (evn->signal) {
	case SIG_INIT:
		break;
	case SIG_LIGHT_ON:
		processLightOn(evn);
		break;
	case SIG_LIGHT_OFF:
		processLightOff(evn);
		break;
	}
}

static void processLightOn(event_t * evn) {
	system_general_status_t systemGeneralStatus = getGeneralSystemStatus();
	switch (systemGeneralStatus) {
	case LEARNING_WAITING_GREEN_LIGHT:
		if (evn->ledName == GREEN_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_ON, GREEN_LED);
		}
		break;
	case LEARNING_WAITING_RED_LIGHT:
		if (evn->ledName == RED_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_ON, RED_LED);
		}
		break;
	case RUNNING:
		processLightOnRunning(evn);
		break;
	}
}

static void processLightOff(event_t * evn) {
	system_general_status_t systemGeneralStatus = getGeneralSystemStatus();
	switch (systemGeneralStatus) {
	case LEARNING_WAITING_GREEN_LIGHT:
		if (evn->ledName == GREEN_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_OFF, GREEN_LED);
		}
		break;
	case LEARNING_WAITING_RED_LIGHT:
		if (evn->ledName == RED_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_OFF, RED_LED);
		}
		break;
	case RUNNING:
		processLightOffRunning(evn);
		break;
	}
}

static void processLightOnRunning(event_t * evn) {

}

static void processLightOffRunning(event_t * evn) {

}
