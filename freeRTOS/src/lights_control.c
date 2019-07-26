#include "lights_control.h"
#include "status_control.h"
#include "event.h"
#include "soniforo.h"
#include "rtos_service.h"

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
			putLightEvent(lightsTimeModule, SIG_LIGHT_GREEN_ON, GREEN_LED); //check
			putEvent(statusModule, SIG_LEARNING_WAITING_RED_LIGHT);
		}
		break;
	case LEARNING_WAITING_RED_LIGHT:
		if (evn->ledName == RED_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_RED_ON, RED_LED);//check
			putEvent(statusModule, SIG_LEARNING_AGAIN_GREEN_LIGHT_ON);
		}
		break;
	case LEARNING_WAITING_AGAIN_GREEN_LIGHT:
		if (evn->ledName == GREEN_LED) {
			putLightEvent(lightsTimeModule, SIG_LIGHT_GREEN_ON_AGAIN, GREEN_LED); //check
			putEvent(statusModule, SIG_LEARNING_FINISH);
		}
		break;
	case RUNNING_INIT:
		if (evn->ledName == RED_LED) {
			putEvent(statusModule, SIG_RUNNING_INIT);
			putEvent(broadcastModule, SIG_CROSS);
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
	case RUNNING:
		processLightOffRunning(evn);
		break;
	}
}

static void processLightOnRunning(event_t * evn) {
	system_general_status_t systemGeneralStatus = getGeneralSystemStatus();
		switch (systemGeneralStatus) {
		case RUNNING:
			if (evn->ledName == GREEN_LED) {
				//
				putEvent(broadcastModule, SIG_WAIT);
			} else if ((evn->ledName == RED_LED)) {
				//xTimerStart(redLightTimerHandle, 0);
				putEvent(broadcastModule, SIG_CROSS);
			}
			break;
		}
}

static void processLightOffRunning(event_t * evn) {

}
