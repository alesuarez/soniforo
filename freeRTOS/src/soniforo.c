#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "sapi.h"

#include "debounce_fsm.h"
#include "key_service.h"

DEBUG_PRINT_ENABLE
;

StackType_t myTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t myTaskTCB;
bool_t recording = TRUE;
TickType_t totalTicks;
gpioMap_t pressedKey;

void welcomeTask(void *taskParmPtr) {
	// ---------- CONFIGURACIONES ------------------------------
	printf("Blinky con freeRTOS y sAPI.\r\n");

	gpioWrite(LED1, ON);
	// Envia la tarea al estado bloqueado durante 1 s (delay)
	vTaskDelay(1000 / portTICK_RATE_MS);
	gpioWrite(LED1, OFF);

	// Tarea periodica cada 500 ms
	portTickType xPeriodicity = 500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	// ---------- REPETIR POR SIEMPRE --------------------------
	while (TRUE) {
		gpioToggle(LEDB);
		printf("Blink!\r\n");
		// Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void recodTimeTask(void *taskParmPtr) {
	debounceData_t tec1Key;
	initDebounceFsm(&tec1Key, TEC1);

	TickType_t initTime = xTaskGetTickCount();

	TickType_t ticksToPress = 0;

	while (TRUE) {
		if (recording) {
			if (ticksToPress == 0
					&& getDebounceFsm(&tec1Key, pressedKey)) {
				ticksToPress = xTaskGetTickCount();
			} else if (ticksToPress > 0
					&& !getDebounceFsm(&tec1Key, pressedKey)) {
				totalTicks = xTaskGetTickCount() - ticksToPress;
				ticksToPress = 0;
				recording = FALSE;
			}
		}

		vTaskDelayUntil(&initTime, 40 / portTICK_RATE_MS);
	}
}

void playTimeTask() {
	TickType_t initTime = xTaskGetTickCount();

	while (TRUE) {

		if (!recording) {
			gpioWrite(LED1, ON);
			vTaskDelay(totalTicks);
			gpioWrite(LED1, OFF);
			recording = 1;
		}
		vTaskDelayUntil(&initTime, 10 / portTICK_RATE_MS);
	}
}

int main(void) {
	boardConfig();

	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintlnString("Blinky con freeRTOS y sAPI.");

	// Led para dar se�al de vida
	gpioWrite(LED3, ON);

	xTaskCreate(recodTimeTask,                 // Funcion de la tarea a ejecutar
			(const char *) "recodTimeTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(playTimeTask,                  // Funcion de la tarea a ejecutar
			(const char *) "playTime", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	vTaskStartScheduler();

	while ( TRUE) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
		gpioWrite(LED3, ON);
	}

	return 0;
}
