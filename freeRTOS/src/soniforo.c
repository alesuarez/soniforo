#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
#include "sapi.h"

#include "soniforo.h"

#define RED_LED_PORT			GPIO0
#define YELLOW_LED_PORT			GPIO1
#define GREEN_LED_PORT 			GPIO2

#define ESP01_UART 				UART_232
#define DEFAULT_BAUD_RATE 		115200

#define CH0						0
#define CH1						1
#define CH2						2
#define GPIO_3					3
#define PIN_0					0
#define PIN_3					3
#define PIN_4					4

#define ISR_PRIORITY			5

CONSOLE_PRINT_ENABLE
DEBUG_PRINT_ENABLE

static void esp01Task(void *); 				// tarea encargada de configurar la ESP01
static void ligthRedTask(void *); 			// tarea de atender a la interrucion de la luz roja
static void ligthYellowTask(void *); 		// tarea de atender a la interrucion de la luz amarilla
static void ligthGreenTask(void *); 		// tarea de atender a la interrucion de la luz verde
static void receiveQueueTask(void *); 		// tarea que recibe los mensajes
static void sendStatusToEsp01Task(void *); 	// tarea encargada de enviar mensajes a la ESP01

static void copyMessage(struct Message, struct Message *);
static void decideAction(struct Message, struct Message);
static bool_t sendCmd(CommandEsp8266_t); // envia un comando a la ESP01

static void initIRQ(); 			// configuracion de las interrupciones del micro
void GPIO0_IRQHandler(void); 	// handler de la luz roja
void GPIO1_IRQHandler(void); 	// handler de la luz amarilla
void GPIO2_IRQHandler(void); 	// handler de la luz verde

SemaphoreHandle_t xsRedLightOff = NULL;
SemaphoreHandle_t xsRedLigthOn = NULL;

SemaphoreHandle_t xsYellowLightOff = NULL;
SemaphoreHandle_t xsYellowLigthOn = NULL;

SemaphoreHandle_t xsGreenLightOff = NULL;
SemaphoreHandle_t xsGreenLigthOn = NULL;

TaskHandle_t sendStatusToEthernetHandle;
TaskHandle_t ligthYellowTaskHandle;
TaskHandle_t ligthGreenTaskHandle;
TaskHandle_t ligthRedTaskHandle;
TaskHandle_t sendTaskHandle;
TaskHandle_t esp01TaskHandle;

static void esp01Task(void *p) {

	gpioWrite(LEDR, ON);

	consolePrintConfigUart(ESP01_UART, DEFAULT_BAUD_RATE);
	debugPrintConfigUart(UART_USB, DEFAULT_BAUD_RATE );

	for (int i = 0; i < COMMAND_INIT_LENGHT; i++) {
		sendCmd(initVector[i]);
		vTaskDelay(5000 / portTICK_RATE_MS);
	}

	vTaskResume(ligthRedTaskHandle);	// una vez iniciada correctamente
	vTaskResume(ligthYellowTaskHandle); // la placa inicio las tareas
	vTaskResume(ligthGreenTaskHandle);	// que atienden las luces

	initIRQ();							// configuro las interrupciones

	gpioWrite(LEDR, OFF);				// apago el led rojo

	vTaskSuspend(esp01TaskHandle); 		// suspendo esta tarea
}

static void ligthRedTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthRedTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	while (1) {

		if ( xSemaphoreTake( xsRedLigthOn, portMAX_DELAY) == pdTRUE) { // si detecto bajo - alto
			if (gpioRead(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;
				ligthRedTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsRedLightOff, portMAX_DELAY) == pdTRUE) { // si detecto alto - bajo
			if (!gpioRead(RED_LED_PORT)) {
				ligthRedTask_Message.Led = RED_LED;						// para esta version no se tuvo en cuenta el estado
				ligthRedTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthRedTask_Message, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

static void ligthYellowTask(void *p) {
	xQueueHandle Buffer = *(xQueueHandle *) p;
	struct Message ligthYellowTask_Message;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsYellowLigthOn, portMAX_DELAY) == pdTRUE) { 	// si detecto bajo - alto
			if (gpioRead(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;
				ligthYellowTask_Message.Status = LED_ON;
				xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsYellowLightOff, portMAX_DELAY) == pdTRUE) { 	// si detecto alto - bajo
			if (!gpioRead(YELLOW_LED_PORT)) {
				ligthYellowTask_Message.Led = YELLOW_LED;					// para esta version no se tuvo en cuenta el estado
				ligthYellowTask_Message.Status = LED_OFF;
				// xQueueSend(Buffer, &ligthYellowTask_Message, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

static void ligthGreenTask(void *p) {
	xQueueHandle buffer = *(xQueueHandle *) p;
	struct Message ligthGreenTaskMessage;

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();
	while (1) {
		if ( xSemaphoreTake( xsGreenLigthOn, portMAX_DELAY) == pdTRUE) { 	// si detecto bajo - alto
			if (gpioRead(GREEN_LED_PORT)) {
				ligthGreenTaskMessage.Led = GREEN_LED;
				ligthGreenTaskMessage.Status = LED_ON;
				xQueueSend(buffer, &ligthGreenTaskMessage, portMAX_DELAY);
			}
		}

		if ( xSemaphoreTake( xsGreenLightOff, portMAX_DELAY) == pdTRUE) { 	// si detecto alto - bajo
			if (!gpioRead(GREEN_LED_PORT)) {
				ligthGreenTaskMessage.Led = GREEN_LED;						// para esta version no se tuvo en cuenta el estado
				ligthGreenTaskMessage.Status = LED_OFF;
				// xQueueSend(buffer, &ligthGreenTaskMessage, portMAX_DELAY);
			}
		}

		//vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

static void receiveQueueTask(void * a) {
	xQueueHandle buffer = *(xQueueHandle *) a;
	struct Message sendingMessage;
	static struct Message oldMessage;
	while (1) {
		if (xQueueReceive(buffer, &sendingMessage, portMAX_DELAY)) {
			decideAction(sendingMessage, oldMessage);
			copyMessage(sendingMessage, &oldMessage);
			vTaskDelay(1 / portTICK_RATE_MS);
		}
	}
}

static void sendStatusToEsp01Task(void * a) {
	while (1) {
		debugPrintlnString("Cruzar\r\n");
		sendCmd(CMD_CIPSEND);
		consolePrintString("Cruzar\r\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

static bool_t sendCmd(CommandEsp8266_t cmd) {
	bool_t retValue = FALSE;

	debugPrintString(">>>> Enviando ");
	debugPrintlnString(CommandEsp8266ToString[cmd]);

	consolePrintString(CommandEsp8266ToString[cmd]);

	retValue = waitForReceiveStringOrTimeoutBlocking( ESP01_UART,
			esp01Responses[cmd], 4, 5000);

	if (retValue) {
		debugPrintString(">>>>    Exito al enviar : ");
		debugPrintlnString(CommandEsp8266ToString[cmd]);
	} else {
		debugPrintString(">>>>    Error al enviar : ");
		debugPrintlnString(CommandEsp8266ToString[cmd]);
		return retValue;
	}

	return TRUE;
}

static void copyMessage(struct Message src, struct Message * dst) {
	dst->Led = src.Led;
	dst->Status = src.Status;
	dst->Time = src.Time;
}

static void decideAction(struct Message new, struct Message old) {
	// todo: In this implementation the turn off leds states were not taken into account

	vTaskSuspend(sendStatusToEthernetHandle);

	if (old.Led == YELLOW_LED && new.Led == GREEN_LED) { // el semaforo esta en verde
		debugPrintlnString("Cruzar\r\n");
		vTaskResume(sendStatusToEthernetHandle);
		return;
	}

	if (old.Led == GREEN_LED && new.Led == YELLOW_LED) { // el semaforo se esta por poner en rojo
		debugPrintlnString("Apurate\r\n");
		return;
	}

	debugPrintlnString("Esperar\r\n"); // cualquier otro estado el sistema indica que no se puede cruzar
	return;

}

static void initIRQ() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(CH0, GPIO_3, PIN_0); 				//Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0); 	//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH0);
	NVIC_SetPriority(PIN_INT0_IRQn, ISR_PRIORITY);
	NVIC_EnableIRQ(PIN_INT0_IRQn);

	Chip_SCU_GPIOIntPinSel(CH1, GPIO_3, PIN_3);

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1);
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH1);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1);
	NVIC_SetPriority(PIN_INT1_IRQn, ISR_PRIORITY);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	Chip_SCU_GPIOIntPinSel(CH2, GPIO_3, PIN_4);

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH2);
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH2);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH2);
	NVIC_SetPriority(PIN_INT2_IRQn, ISR_PRIORITY);
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

	static xQueueHandle sendBuffer;

	boardConfig();

	debugPrintConfigUart( UART_USB, DEFAULT_BAUD_RATE );
	debugPrintlnString("Inicio de programa... \r\n");

	xsRedLightOff = xSemaphoreCreateBinary();
	xsRedLigthOn = xSemaphoreCreateBinary();

	xsYellowLightOff = xSemaphoreCreateBinary();
	xsYellowLigthOn = xSemaphoreCreateBinary();

	xsGreenLightOff = xSemaphoreCreateBinary();
	xsGreenLigthOn = xSemaphoreCreateBinary();

	sendBuffer = xQueueCreate(10, sizeof(struct Message));

	gpioWrite(LED3, ON);

	// Crear tarea en freeRTOS
	xTaskCreate(ligthRedTask,
			(const char *) "ligthRedTask",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 7,
			&ligthRedTaskHandle
			);

	xTaskCreate(ligthYellowTask,
			(const char *) "ligthYellowTask",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 7,
			&ligthYellowTaskHandle
			);

	xTaskCreate(ligthGreenTask,
			(const char *) "ligthGreenTask",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 7,
			&ligthGreenTaskHandle
			);

	xTaskCreate(receiveQueueTask,
			(const char *) "send",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 1,
			&sendTaskHandle
			);

	xTaskCreate(sendStatusToEsp01Task,
			(const char *) "sendStatusToEthernet",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 1,
			&sendStatusToEthernetHandle
			);

	xTaskCreate(esp01Task,
			(const char *) "esp01Task",
			configMINIMAL_STACK_SIZE * 2,
			&sendBuffer,
			tskIDLE_PRIORITY + 1,
			&esp01TaskHandle
			);

	vTaskSuspend(sendStatusToEthernetHandle);

	vTaskSuspend(ligthRedTaskHandle);
	vTaskSuspend(ligthYellowTaskHandle);
	vTaskSuspend(ligthGreenTaskHandle);

	vTaskStartScheduler();

	while ( TRUE) {
		gpioWrite(LED1, ON);
		gpioWrite(LED2, ON);
		gpioWrite(LED3, ON);
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
	}

	return 0;
}
