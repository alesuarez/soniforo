#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "debounce_fsm.h"
// sAPI header
#include "sapi.h"

#define RED_LED_PORT		GPIO0
#define YELLOW_LED_PORT		GPIO1
#define GREEN_LED_PORT 		GPIO2

DEBUG_PRINT_ENABLE
;

SemaphoreHandle_t xsRedLightOff = NULL;
SemaphoreHandle_t xsRedLigthOn = NULL;

SemaphoreHandle_t xsYellowLightOff = NULL;
SemaphoreHandle_t xsYellowLigthOn = NULL;

SemaphoreHandle_t xsGreenLightOff = NULL;
SemaphoreHandle_t xsGreenLigthOn = NULL;

typedef enum{
	LED_ON,
	LED_OFF
} Led_Status;

typedef enum{
	RED_LED,
	YELLOW_LED,
	GREEN_LED
} Led_Name;

struct Message { //Estructura con formato del mensaje
	Led_Name Led;
	Led_Status Status;
	int32_t Time;
};

void ligthRedTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthRedTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	while (1) {

		if ( xSemaphoreTake( xsRedLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;
				ligthRedTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsRedLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;
				ligthRedTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ligthYellowTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthYellowTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsYellowLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;
				ligthYellowTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsYellowLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;
				ligthYellowTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ligthGreenTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthGreenTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsGreenLigthOn, portMAX_DELAY) == pdTRUE) {
			if (gpioRead(GREEN_LED_PORT)) {
				ligthGreenTask_Message.Led = GREEN_LED;
				ligthGreenTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthGreenTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsGreenLightOff, portMAX_DELAY) == pdTRUE) {
			if (!gpioRead(GREEN_LED_PORT)) {
				ligthGreenTask_Message.Led = GREEN_LED;
				ligthGreenTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthGreenTask_Message, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void copyMessage(struct Message src, struct Message * dst) {
	dst->Led = src.Led;
	dst->Status = src.Status;
	dst->Time = src.Time;
}

void decideAction(struct Message new, struct Message old) {
	// todo: In this implementation the turn off leds states were not taken into account
	if (old.Led == YELLOW_LED && new.Led == GREEN_LED){
		debugPrintlnString("Cruzar\r\n");
		return;
	}

	if (old.Led == GREEN_LED && new.Led == YELLOW_LED) {
		debugPrintlnString("Apurate\r\n");
		return;
	}

	debugPrintlnString("Esperar\r\n");
	return;

}

void Send(void * a) {
	xQueueHandle Buffer = *(xQueueHandle *) a;
	struct Message Sending_Message;
	static struct Message oldMessage;
	while (1) {

		if (xQueueReceive(Buffer, &Sending_Message, portMAX_DELAY)){
			decideAction(Sending_Message, oldMessage);
			copyMessage(Sending_Message, &oldMessage);
			vTaskDelay(1 / portTICK_RATE_MS);
		}
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

	static xQueueHandle Send_Buf;

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

	Send_Buf = xQueueCreate(10,sizeof(struct Message));

	gpioWrite(LED3, ON);

	// Crear tarea en freeRTOS
	xTaskCreate(ligthRedTask,                  // Funcion de la tarea a ejecutar
			(const char *) "ligthRedTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			&Send_Buf,                          // Parametros de tarea
			tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(ligthYellowTask,               // Funcion de la tarea a ejecutar
			(const char *) "ligthYellowTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			&Send_Buf,                          // Parametros de tarea
			tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(ligthGreenTask,               // Funcion de la tarea a ejecutar
			(const char *) "ligthGreenTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			&Send_Buf,                          // Parametros de tarea
			tskIDLE_PRIORITY + 7,         // Prioridad de la tarea
			0                         // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(Send,               // Funcion de la tarea a ejecutar
			(const char *) "Send", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, // Cantidad de stack de la tarea
			&Send_Buf,                          // Parametros de tarea
			tskIDLE_PRIORITY + 1,         // Prioridad de la tarea
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
