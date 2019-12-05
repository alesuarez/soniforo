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
	adcConfig(ADC_ENABLE); /* ADC */
	dacConfig(DAC_ENABLE); /* DAC */
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
	//debounceModule 		= registerModule(debounceHandler);
	broadcastModule		= registerModule(broadcastHandler);

	initAllModules();
	initQueues();
	initSemaphores();

	IRQ_init();
	timer0Init(10000);

	vTaskStartScheduler();

	while (TRUE) {
		gpioWrite(LED1, ON);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, ON);
	}

	return 0;
}

