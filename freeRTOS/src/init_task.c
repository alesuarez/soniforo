#include "init_task.h"
#include "event_framework.h"
#include "event.h"
#include "soniforo.h"

void initTask(void *p) {
	vTaskDelete(initTaskHandle);
}

