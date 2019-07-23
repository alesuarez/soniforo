#include "event_queue_task.h"
#include "rtos_service.h"
#include "event.h"

void eventQueueTask(void * p) {
	event_t evn;
	while(1) {
		xQueueReceive(eventQueue, &evn, portMAX_DELAY);
		fsm_ptr eventHandler = (evn.receptor)->eventHandler;
		eventHandler(&evn);
	}
}


