#include "broadcast.h"
#include "sapi.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timers.h"
#include "rtos_service.h"

void broadcastHandler(event_t * evn) {
	switch (evn->signal) {
	case SIG_INIT:
		break;
	case SIG_WAIT:
		xTimerStart(greenLightTimerHandle, 0);
		gpioWrite(LED1, ON); //rojo
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, OFF);
		break;
	case SIG_CROSS:
		xTimerStart(redLightTimerHandle, 0);
		gpioWrite(LED1, OFF);
		gpioWrite(LED2, OFF);
		gpioWrite(LED3, ON);//verde
		break;
	case SIG_CAUTION:
		xTimerStop(redLightTimerHandle, 0);
		xTimerStart(yellowLightTimerHandle, 0);
		gpioWrite(LED1, OFF);
		gpioWrite(LED3, OFF);
		gpioWrite(LED2, ON);//vamarillo
		break;
	}
}
