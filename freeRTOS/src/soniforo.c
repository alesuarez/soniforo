#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "debounce_fsm.h"
// sAPI header
#include "sapi.h"

DEBUG_PRINT_ENABLE
;

SemaphoreHandle_t xsRedLightOff = NULL;
SemaphoreHandle_t xsRedLigthOn = NULL;

SemaphoreHandle_t xsYellowLightOff = NULL;
SemaphoreHandle_t xsYellowLigthOn = NULL;

SemaphoreHandle_t xsGreenLightOff = NULL;
SemaphoreHandle_t xsGreenLigthOn = NULL;

void ligthRedTask(void *p) {
	debounceData_t redInput;
	initDebounceFsm(&redInput, GPIO0);
	portTickType xPeriodicity = 40 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsRedLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(GPIO0)) {
				debugPrintlnString("R\n");
			}
		}

		if ( xSemaphoreTake( xsRedLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(GPIO0)) {
				debugPrintlnString("r\n");
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ligthYellowTask(void *p) {
	portTickType xPeriodicity = 40 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsYellowLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(GPIO1)) {
				debugPrintlnString("A\n");
			}
		}

		if ( xSemaphoreTake( xsYellowLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(GPIO1)) {
				debugPrintlnString("a\n");
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ligthGreenTask(void *p) {
	portTickType xPeriodicity = 40 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsGreenLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(GPIO2)) {
				debugPrintlnString("V\n");
			}
		}

		if ( xSemaphoreTake( xsGreenLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(GPIO2)) {
				debugPrintlnString("v\n");
			}
		}

		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void initIRQ() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(0, 3, 0); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH0); //Se configura para que el
	NVIC_SetPriority(PIN_INT0_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT0_IRQn);

	Chip_SCU_GPIOIntPinSel(1, 3, 3); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH1); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1); //Se configura para que el
	NVIC_SetPriority(PIN_INT1_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	Chip_SCU_GPIOIntPinSel(2, 3, 4); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH2); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH2); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH2); //Se configura para que el
	NVIC_SetPriority(PIN_INT2_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT2_IRQn);
}

void GPIO0_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsRedLightOff, &xSwitchRequired); //En este caso libero un semáforo
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsRedLigthOn, &xSwitchRequired); //En este caso libero un semáforo
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO1_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsYellowLightOff, &xSwitchRequired); //En este caso libero un semáforo
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsYellowLigthOn, &xSwitchRequired); //En este caso libero un semáforo
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO2_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsGreenLightOff, &xSwitchRequired); //En este caso libero un semáforo
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR(xsGreenLigthOn, &xSwitchRequired); //En este caso libero un semáforo
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

int main(void) {
	boardConfig();

	xsRedLightOff = xSemaphoreCreateBinary();
	xsRedLigthOn = xSemaphoreCreateBinary();

	xsYellowLightOff = xSemaphoreCreateBinary();
	xsYellowLigthOn = xSemaphoreCreateBinary();

	xsGreenLightOff = xSemaphoreCreateBinary();
	xsGreenLigthOn = xSemaphoreCreateBinary();

	initIRQ();

	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintlnString("Inicio de programa... \r\n");

	gpioWrite(LED3, ON);

	// Crear tarea en freeRTOS
	xTaskCreate(ligthRedTask,                  // Funcion de la tarea a ejecutar
			(const char *) "ligthRedTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 4, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(ligthYellowTask,               // Funcion de la tarea a ejecutar
			(const char *) "ligthYellowTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 4, // Cantidad de stack de la tarea
			0,                          // Parametros de tarea
			tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(ligthGreenTask,               // Funcion de la tarea a ejecutar
				(const char *) "ligthGreenTask", // Nombre de la tarea como String amigable para el usuario
				configMINIMAL_STACK_SIZE * 4, // Cantidad de stack de la tarea
				0,                          // Parametros de tarea
				tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
				0                         // Puntero a la tarea creada en el sistema
				);

	// Iniciar scheduler
	vTaskStartScheduler();

	// ---------- REPETIR POR SIEMPRE --------------------------
	while ( TRUE) {
		gpioWrite(LED3, OFF);
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}

	// NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
	// directamenteno sobre un microcontroladore y no es llamado por ningun
	// Sistema Operativo, como en el caso de un programa para PC.
	return 0;
}
