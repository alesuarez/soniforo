#include "configuration_control.h"
#include "event.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "rtos_service.h"

extern module_t * statusModule;

void configurationHandler( event_t * evn ) {
	switch( evn->signal ) {
		case SIG_INIT:
			break;
		case SIG_CONFIGURING_INIT:
			vTaskResume(esp01TaskHandle);
			break;
		case SIG_CONFIGURING_FINISH:
			vTaskSuspend(configurationTaskHandle);
			gpioWrite(LED3, ON);
			gpioWrite(LED2, ON);
			putEvent(statusModule, SIG_CONFIGURING_FINISH);
			break;
	}
}
