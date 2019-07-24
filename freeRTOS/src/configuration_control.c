#include "configuration_control.h"
#include "event.h"
#include "cfg_warng_devices.h"
#include "alive_task.h"

extern module_t * statusModule;

void configurationHandler( event_t * evn ) {
	switch( evn->signal ) {
		case SIG_INIT:
			break;
		case SIG_CONFIGURING_INIT:
			vTaskResume(esp01ConfigurationTaskHandle);
			break;
		case SIG_CONFIGURING_FINISH:
			vTaskSuspend(ledBlinkingInConfigurationTaskHandle);
			gpioWrite(LEDG, ON);
			putEvent(statusModule, SIG_CONFIGURING_FINISH);
			break;
	}
}
