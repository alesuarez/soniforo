#include "status_control.h"
#include "event.h"
#include "soniforo.h"
#include "commons.h"
#include "task.h"
#include "rtos_service.h"

extern system_general_status_t systemStatus;
extern module_t * configurationModule;

void statusHandler( event_t * evn ) {
	switch( evn->signal ) {
		case SIG_INIT:
			setGeneralSystemStatus(INIT);
			break;
		case SIG_CONFIGURING_INIT:
			setGeneralSystemStatus(CONFIGURING);
			putEvent(configurationModule, SIG_CONFIGURING_INIT);
			break;
		case SIG_CONFIGURING_FINISH:
		case SIG_LEARNING_INIT:
			setGeneralSystemStatus(LEARNING_WAITING_GREEN_LIGHT);
			break;
		case SIG_LEARNING_WAITING_GREEN_LIGHT:
			setGeneralSystemStatus(LEARNING_WAITING_GREEN_LIGHT);
			break;
		case SIG_LEARNING_WAITING_RED_LIGHT:
			setGeneralSystemStatus(LEARNING_WAITING_RED_LIGHT);
			break;
		case SIG_LEARNING_AGAIN_GREEN_LIGHT_ON:
			setGeneralSystemStatus(LEARNING_WAITING_AGAIN_GREEN_LIGHT);
			break;
		case SIG_LEARNING_FINISH:
			createLightAdvertisementTimers(); //configuracion de los timers
			setGeneralSystemStatus(RUNNING_INIT); //wait again for red ligh
			gpioToggle(LEDB);
			break;
		case SIG_RUNNING_INIT:
			gpioToggle(LEDR);
			setGeneralSystemStatus(RUNNING);
			break;
	}
}

system_general_status_t getGeneralSystemStatus() {
	system_general_status_t systemGeneralStatus;

	taskENTER_CRITICAL();
	systemGeneralStatus = systemStatus;
	taskEXIT_CRITICAL();

	return systemGeneralStatus;
}

void setGeneralSystemStatus(system_general_status_t systemGeneralStatus) {
	taskENTER_CRITICAL();
	systemStatus = systemGeneralStatus;
	taskEXIT_CRITICAL();
}
