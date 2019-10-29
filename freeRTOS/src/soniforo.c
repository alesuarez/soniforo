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
#include "debounce_control.h"
#include "broadcast.h"

int main(void) {

	boardConfig();

	UART_init();

	// Crear tarea en freeRTOS
	createAllTasks();

	suspendSelectedTasks();

	createInitConfigurationTimer();
	createLightDebounceTimers();

	statusModule 		= registerModule(statusHandler);
	configurationModule = registerModule(configurationHandler);
	learningModule 		= registerModule(learningHandler);
	lightsModule 		= registerModule(lightsHandler);
	lightsTimeModule 	= registerModule(lightsTimeHandler);
	debounceModule 		= registerModule(debounceHandler);
	broadcastModule		= registerModule(broadcastHandler);

	initAllModules();
	initQueues();
	initSemaphores();

	IRQ_init();

	vTaskStartScheduler();

	while (TRUE) {
		gpioWrite(LED1, ON);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, ON);
	}

	return 0;
}

