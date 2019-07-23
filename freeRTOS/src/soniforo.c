#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "sapi.h"
#include "commons.h"
#include "peripheral_driver.h"
#include "rtos_service.h"
#include "soniforo.h"
#include "status_control.h"
#include "configuration_control.h"
#include "learning_control.h"
#include "lights_control.h"
#include "lights_time_control.h"

int main(void) {

	boardConfig();



	// Crear tarea en freeRTOS
	create_all_tasks();
	suspend_selected_tasks();
/*
	statusModule = registerModule(statusHandler);
	configurationModule = registerModule(configurationHandler);
	learningModule = registerModule(learningHandler);
	lightsModule = registerModule(lightsHandler);
	lightsTimeModule = registerModule(lightsTimeHandler);

	initAllModules();*/
	init_queues();

	IRQ_init();
	vTaskStartScheduler();


	while ( TRUE) {
	}

	return 0;
}

