#include "event.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "rtos_service.h"

extern QueueHandle_t eventQueue;

void putEvent(module_t * module, signal_t signal) {
	event_t evn;
	evn.receptor = module;
	evn.signal = signal;

	xQueueSend(eventQueue, &evn, 0);
}

void putLightEvent(module_t * module, signal_t signal, led_name_t ledName) {
	event_t evn;
	evn.receptor = module;
	evn.signal = signal;
	evn.ledName = ledName;

	xQueueSend(eventQueue, &evn, 0);
}

portBASE_TYPE putEventFromISR(module_t * module, signal_t signal, led_name_t ledName) {
	portBASE_TYPE cambiarCtx = pdFALSE;
	event_t evn;
	evn.receptor = module;
	evn.signal = signal;
	evn.ledName = ledName;

	xQueueSendFromISR(eventQueue, &evn, &cambiarCtx);
	return cambiarCtx;
}

void resendEvent (module_t * module, event_t * evn) {
	putLightEvent(module, evn->signal, evn->ledName);
}
