#include "lights_control.h"
#include "status_control.h"
#include "event.h"
#include "soniforo.h"
#include "rtos_service.h"

static void processLightOn(event_t * evn, system_general_status_t systemGeneralStatu);
static void processLightOff(event_t * evn, system_general_status_t systemGeneralStatu);
static void processLightOnRunning(event_t * evn, system_general_status_t systemGeneralStatu);
static void processLightOffRunning(event_t * evn, system_general_status_t systemGeneralStatu);
static void saveLedStatus(led_name_t Led);

led_name_t previusLed;


void lightsHandler(event_t * evn) {
	system_general_status_t systemGeneralStatus = getGeneralSystemStatus();

	switch (evn->signal) {
	case SIG_INIT:
		break;
	case SIG_LIGHT_ON:
		processLightOn(evn, systemGeneralStatus);
		break;
	case SIG_LIGHT_OFF:
		processLightOff(evn, systemGeneralStatus);
		break;
	}
}

static void processLightOn(event_t * evn, system_general_status_t systemGeneralStatus) {

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
				previusLed = RED_LED;
				putEvent(statusModule, SIG_RUNNING_INIT);
				putEvent(broadcastModule, SIG_CROSS);
			}
			break;
		case RUNNING:
			processLightOnRunning(evn, systemGeneralStatus);
			break;
	}
}

static void processLightOff(event_t * evn, system_general_status_t systemGeneralStatus) {
	switch (systemGeneralStatus) {
		case RUNNING:
			processLightOffRunning(evn, systemGeneralStatus);
			break;
	}
}

static void processLightOnRunning(event_t * evn, system_general_status_t systemGeneralStatu) {
	saveLedStatus(evn->ledName);
	switch (systemGeneralStatu) {
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

static void processLightOffRunning(event_t * evn, system_general_status_t systemGeneralStatu) {

}

static void saveLedStatus(led_name_t led) {
	if (previusLed == led) {
		gpioWrite(LED1, ON); //rojo
		gpioWrite(LED2, ON);
		gpioWrite(LED3, ON);
		gpioWrite(LEDR, ON);
		gpioWrite(LEDG, ON);
		gpioWrite(LEDB, ON);
		//putEvent(broadcastModule, SIG_WAIT);
		//putEvent(statusModule, SIG_LEARNING_INIT);

		//Error
	} else {
		previusLed = led;
	}
	//semaforo apagado actualizar un timer
}
