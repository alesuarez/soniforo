#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
// sAPI header
#include "sapi.h"

DEBUG_PRINT_ENABLE
;

SemaphoreHandle_t xSemaphoreTEC1 = NULL;

void tec1(void *p) {
	portTickType xPeriodicity = 500 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xSemaphoreTEC1, portMAX_DELAY) == pdTRUE) {
			debugPrintlnString("Tecla 1 task \r\n.");
			vTaskDelay(2000);

		}
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void initIRQ() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(0, 0, 4); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0);//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);//Se configura para que el

	NVIC_EnableIRQ(PIN_INT0_IRQn);
}

void GPIO0_IRQHandler(void){
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0){ //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		xSemaphoreGiveFromISR( xSemaphoreTEC1, &xSwitchRequired ); //En este caso libero un semáforo
	}

	portEND_SWITCHING_ISR(xSwitchRequired);//Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);

}

int main(void) {
	boardConfig();

	initIRQ();

	debugPrintConfigUart( UART_USB, 115200 );
	debugPrintlnString("Inicio de programa... \r\n");

	xSemaphoreTEC1 = xSemaphoreCreateBinary();

	gpioWrite(LED3, ON);

	// Crear tarea en freeRTOS
	xTaskCreate(tec1,                     // Funcion de la tarea a ejecutar
				(const char *) "tec1", // Nombre de la tarea como String amigable para el usuario
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
