#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "semphr.h"
// sAPI header
#include "sapi.h"

#define RED_LED_PORT			GPIO0
#define YELLOW_LED_PORT			GPIO1
#define GREEN_LED_PORT 			GPIO2
#define MAX_COMMAND_LENGHT	 	45
#define COMMAND_INIT_LENGHT	 	12
#define ESP01_UART 				UART_232
#define DEFAULT_BAUD_RATE 		115200

CONSOLE_PRINT_ENABLE
DEBUG_PRINT_ENABLE

void initIRQ();

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

typedef enum {
	LED_ON, LED_OFF
} Led_Status;

typedef enum {
	RED_LED, YELLOW_LED, GREEN_LED
} Led_Name;

struct Message { //Estructura con formato del mensaje
	Led_Name Led;
	Led_Status Status;
	int32_t Time;
};

typedef enum CommandEsp8266 {
	CMD_AT, //1
	CMD_RST, //2
	CMD_CWMODE_1, //3
	CMD_CWMODE_2, //4
	CMD_CWSAP, //5
	CMD_CWDHCP_0_1, //6
	CMD_CWDHCP_1_1, //7
	CMD_CIPSTART, //8
	CMD_CIPSEND, //9
	CMD_CIPMUX_1, //10
	CMD_CIPDINFO_1, //11
	CMD_CIPSTATUS_Q, //12
	CMD_CWAUTOCONN_0 //13
} CommandEsp8266_t;

static const char CommandEsp8266ToString[][MAX_COMMAND_LENGHT] = { "AT\r\n", //1
		"AT+RST\r\n", //2
		"AT+CWMODE=1\r\n", //3
		"AT+CWMODE=2\r\n", //4
		"AT+CWSAP=\"Soniforo_CIAA\",\"\",10,0\r\n", //5
		"AT+CWDHCP=0,1\r\n", //6
		"AT+CWDHCP=1,1\r\n", //7
		"AT+CIPSTART=3,\"UDP\",\"0\",0,4096,2\r\n", //8
		"AT+CIPSEND=3,8,\"192.168.4.255\",4096\r\n", //9
		"AT+CIPMUX=1\r\n", //10
		"AT+CIPDINFO=1\r\n", //11
		"AT+CIPSTATUS?\r\n", //12
		"AT+CWAUTOCONN=0\r\n" //13
		};

static char esp01Responses[][MAX_COMMAND_LENGHT] = { "AT\r\n", //1
		"AT+RST\r\n", //2
		"CWMODE=1\r\n", //3
		"CWMODE=2\r\n", //4
		"OK\r\n", //5
		"OK\r\n", //6
		"CWDHCP=1,1\r\n", //7
		"3,CONNECT\r\n", //8
		"OK\r\n", //9
		"CIPMUX=1\r\n", //10
		"CIPDINFO=1\r\n", //11
		"STATUS:5\r\n", //12
		"CWAUTOCONN=0\r\n" //13

		};

static CommandEsp8266_t initVector[COMMAND_INIT_LENGHT] = { CMD_AT, CMD_RST,
		CMD_CWMODE_1, CMD_CIPMUX_1, CMD_CIPDINFO_1, CMD_CWAUTOCONN_0,
		CMD_CWDHCP_1_1, CMD_CIPSTATUS_Q, CMD_CWMODE_2, CMD_CWSAP,
		CMD_CWDHCP_0_1, CMD_CIPSTART};

bool_t sendCmd(CommandEsp8266_t cmd) {
	bool_t retVal = FALSE;

	debugPrintString(">>>> Enviando ");
	debugPrintlnString(CommandEsp8266ToString[cmd]);

	consolePrintString(CommandEsp8266ToString[cmd]);

	retVal = waitForReceiveStringOrTimeoutBlocking( ESP01_UART,
			esp01Responses[cmd], 4, 5000);

	if (retVal) {
		debugPrintString(">>>>    Exito al enviar : ");debugPrintlnString(
				CommandEsp8266ToString[cmd]);
	} else {
		debugPrintString(">>>>    Error al enviar : ");debugPrintlnString(
				CommandEsp8266ToString[cmd]);
		return retVal;
	}

	return TRUE;
}
void esp01Task(void *p) {

	portTickType xPeriodicity = 20 / portTICK_RATE_MS;
	portTickType xLastWakeTime = xTaskGetTickCount();

	gpioWrite(LED1, ON);

	consolePrintConfigUart(ESP01_UART, DEFAULT_BAUD_RATE);
	debugPrintConfigUart(UART_USB, DEFAULT_BAUD_RATE );

	for (int i = 0; i < COMMAND_INIT_LENGHT; i++) {
		sendCmd(initVector[i]);
		vTaskDelay(5000 / portTICK_RATE_MS);
	}

	vTaskResume(ligthRedTaskHandle);
	vTaskResume(ligthYellowTaskHandle);
	vTaskResume(ligthGreenTaskHandle);

	initIRQ();

	gpioWrite(LED1, OFF);

	vTaskSuspend(esp01TaskHandle);
}

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
	vTaskSuspend(sendStatusToEthernetHandle);
	if (old.Led == YELLOW_LED && new.Led == GREEN_LED) {
		debugPrintlnString("Cruzar\r\n");
		vTaskResume(sendStatusToEthernetHandle);
		return;
	}

	if (old.Led == GREEN_LED && new.Led == YELLOW_LED) {
		debugPrintlnString("Apurate\r\n");
		return;
	}

	debugPrintlnString("Esperar\r\n");
	return;

}

void send(void * a) {
	xQueueHandle Buffer = *(xQueueHandle *) a;
	struct Message Sending_Message;
	static struct Message oldMessage;
	while (1) {
		if (xQueueReceive(Buffer, &Sending_Message, portMAX_DELAY)) {
			decideAction(Sending_Message, oldMessage);
			copyMessage(Sending_Message, &oldMessage);
			vTaskDelay(1 / portTICK_RATE_MS);
		}
	}
}

void sendStatusToEthernet(void * a) {
	while (1) {
		debugPrintlnString("Cruzar\r\n");
		sendCmd(CMD_CIPSEND);
		consolePrintString("Cruzar\r\n");
		vTaskDelay(500 / portTICK_RATE_MS);
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

	debugPrintConfigUart( UART_USB, DEFAULT_BAUD_RATE );
	debugPrintlnString("Inicio de programa... \r\n");

	xsRedLightOff = xSemaphoreCreateBinary();
	xsRedLigthOn = xSemaphoreCreateBinary();

	xsYellowLightOff = xSemaphoreCreateBinary();
	xsYellowLigthOn = xSemaphoreCreateBinary();

	xsGreenLightOff = xSemaphoreCreateBinary();
	xsGreenLigthOn = xSemaphoreCreateBinary();

	Send_Buf = xQueueCreate(10, sizeof(struct Message));

	gpioWrite(LED3, ON);

	// Crear tarea en freeRTOS
	xTaskCreate(ligthRedTask,
			(const char *) "ligthRedTask",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 7,
			&ligthRedTaskHandle
			);

	xTaskCreate(ligthYellowTask,
			(const char *) "ligthYellowTask",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 7,
			&ligthYellowTaskHandle
			);

	xTaskCreate(ligthGreenTask,
			(const char *) "ligthGreenTask",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 7,
			&ligthGreenTaskHandle
			);

	xTaskCreate(send,
			(const char *) "send",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 1,
			&sendTaskHandle
			);

	xTaskCreate(sendStatusToEthernet,
			(const char *) "sendStatusToEthernet",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 1,
			&sendStatusToEthernetHandle
			);

	xTaskCreate(esp01Task,
			(const char *) "esp01Task",
			configMINIMAL_STACK_SIZE * 2,
			&Send_Buf,
			tskIDLE_PRIORITY + 1,
			&esp01TaskHandle
			);

	vTaskSuspend(sendStatusToEthernetHandle);

	vTaskSuspend(ligthRedTaskHandle);
	vTaskSuspend(ligthYellowTaskHandle);
	vTaskSuspend(ligthGreenTaskHandle);

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
