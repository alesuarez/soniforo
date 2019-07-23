#include "status_control.h"
#include "event.h"
#include "soniforo.h"
#include "commons.h"

extern system_general_status_t systemStatus;
extern module_t * configurationModule;



void statusHandler( event_t * evn ) {
	switch( evn->signal ) {
		case SIG_INIT:
			systemStatus = INIT;
			break;
		case SIG_CONFIGURING_INIT:
			systemStatus = CONFIGURING;

			putEvent(configurationModule, SIG_CONFIGURING_INIT);
			break;
		case SIG_CONFIGURING_FINISH:
		case SIG_LEARNING_INIT:
			systemStatus = SIG_LEARNING_WAITING_GREEN_LIGHT;

			break;
		case SIG_LEARNING_WAITING_GREEN_LIGHT:
			systemStatus = LEARNING_WAITING_GREEN_LIGHT;
			break;
		case SIG_LEARNING_WAITING_RED_LIGHT:
			systemStatus = LEARNING_WAITING_RED_LIGHT;
			break;
		case SIG_LEARNING_FINISH:
			//createTimers(); //configuracion de los timers
			systemStatus = RUNNING;
			break;
		case SIG_RUNNING_INIT:
			systemStatus = RUNNING;
			break;
	}
}

system_general_status_t getGeneralSystemStatus() {
	return systemStatus;
}
