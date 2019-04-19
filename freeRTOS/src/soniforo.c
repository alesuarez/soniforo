
#include "FreeRTOSConfig.h"
#include "board.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "task.h"
#include "sapi.h"

#include "debounce_fsm.h"
#include "key_service.h"
#include "esp01_drive.h"

#define DEFAULT_BAUD_RATE 115200
#define sendToEsp consolePrintString // macro
#define WIFI_MAX_DELAY    6000
#define RED_LIGTH 			GPIO0
#define YELLOW_LIGTH 		GPIO2
#define GREEN_LIGTH 		GPIO4

DEBUG_PRINT_ENABLE
CONSOLE_PRINT_ENABLE

StackType_t myTaskStack[configMINIMAL_STACK_SIZE];
StaticTask_t myTaskTCB;
bool_t recording = TRUE;
TickType_t totalTicks;
TickType_t totalRedTicks;
TickType_t totalYellowTicks;
TickType_t totalGreenTicks;
gpioMap_t pressedKey;
gpioMap_t redLigth;
gpioMap_t yellowLigth;
gpioMap_t greenLigth;
int count = 0;

void welcomeTask(void *taskParmPtr);
void ligthRedTask(void *taskParmPtr);
void ligthYellowTask(void *taskParmPtr);
void ligthGreenTask(void *taskParmPtr);
void playTimeTask(void *taskParmPtr);

TaskHandle_t ligthRedTaskHandle;
TaskHandle_t welcomeTaskHandle;
TaskHandle_t playTaskHandle;

SemaphoreHandle_t redLigthlearningSignal = NULL;
SemaphoreHandle_t yellowLigthlearningSignal = NULL;
SemaphoreHandle_t greenLigthlearningSignal = NULL;

int main(void) {

	// Inicializar la placa
	boardConfig();
	// Configura la UART USB a 115200 baudios
	uartConfig(UART_USB, 115200);
	// Envia un mensaje de bienvenida.

	gpioWrite(LED3, ON);

	redLigthlearningSignal = xSemaphoreCreateMutex();

	yellowLigthlearningSignal = xSemaphoreCreateBinary();
	greenLigthlearningSignal = xSemaphoreCreateBinary();

	xTaskCreate(ligthRedTask,                 // Funcion de la tarea a ejecutar
			(const char *) "ligthRedTask", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, 		// Cantidad de stack de la tarea
			0,                          				// Parametros de tarea
			tskIDLE_PRIORITY + 1,         				// Prioridad de la tarea
			&ligthRedTaskHandle       // Puntero a la tarea creada en el sistema
			);

	xTaskCreate(playTimeTask,                  // Funcion de la tarea a ejecutar
			(const char *) "playTime", // Nombre de la tarea como String amigable para el usuario
			configMINIMAL_STACK_SIZE * 2, 		// Cantidad de stack de la tarea
			0,                          				// Parametros de tarea
			tskIDLE_PRIORITY + 1,         				// Prioridad de la tarea
			&playTaskHandle                         // Puntero a la tarea creada en el sistema
			);



	vTaskStartScheduler();

	while ( TRUE) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
		gpioWrite(LED3, OFF);
	}

	return 0;
}



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
		printf("Welcome to soniforo 0.1v\r\n");
		// Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
		count++;
		if (count == 3) {
			vTaskSuspend(welcomeTaskHandle);
		}
		vTaskDelayUntil(&xLastWakeTime, xPeriodicity);
	}
}

void ligthRedTask(void *taskParmPtr) {
	debounceData_t redInput;
	initDebounceFsm(&redInput, TEC1);

	TickType_t initTime = xTaskGetTickCount();

	TickType_t initRedTicks = 0;
	printf("Pase red task\r\n");
	while (TRUE) {

		printf("Red task tiene el mutex\r\n");
		if (initRedTicks == 0 && getDebounceFsm(&redInput, redLigth)) {
			initRedTicks = xTaskGetTickCount();
			vTaskSuspend(playTaskHandle);
			printf("Grabandooo...\r\n");
		} else if (initRedTicks > 0 && !getDebounceFsm(&redInput, redLigth)) {
			totalRedTicks = xTaskGetTickCount() - initRedTicks;
			initRedTicks = 0;
			vTaskSuspend(ligthRedTaskHandle);
			vTaskResume(playTaskHandle);
		}

		vTaskDelayUntil(&initTime, 50 / portTICK_RATE_MS);
	}
}

void ligthYellowTask(void *taskParmPtr) {
	debounceData_t yellowInput;
	initDebounceFsm(&yellowInput, YELLOW_LIGTH);

	TickType_t initTime = xTaskGetTickCount();

	TickType_t initYellowTicks = 0;

	while (TRUE) {
		if (xSemaphoreTake(redLigthlearningSignal, portMAX_DELAY)) {
			if (initYellowTicks == 0 && getDebounceFsm(&yellowInput, yellowLigth)) {
				initYellowTicks = xTaskGetTickCount();
			} else if (initYellowTicks > 0
					&& !getDebounceFsm(&yellowInput, yellowLigth)) {
				totalYellowTicks = xTaskGetTickCount() - initYellowTicks;
				initYellowTicks = 0;
				xSemaphoreGive(yellowLigthlearningSignal);
			}
		}

		vTaskDelayUntil(&initTime, 50 / portTICK_RATE_MS);
	}
}

void ligthGreenTask(void *taskParmPtr) {
	debounceData_t greenInput;
	initDebounceFsm(&greenInput, GREEN_LIGTH);

	TickType_t initTime = xTaskGetTickCount();

	TickType_t initGreenTicks = 0;

	while (TRUE) {
		if (initGreenTicks == 0 && getDebounceFsm(&greenInput, greenLigth)) {
			initGreenTicks = xTaskGetTickCount();
		} else if (initGreenTicks > 0
				&& !getDebounceFsm(&greenInput, greenLigth)) {
			totalGreenTicks = xTaskGetTickCount() - initGreenTicks;
			initGreenTicks = 0;
			xSemaphoreGive(greenLigthlearningSignal);
		}

		vTaskDelayUntil(&initTime, 50 / portTICK_RATE_MS);
	}
}

void playTimeTask(void *taskParmPtr) {
	TickType_t initTime = xTaskGetTickCount();
	vTaskSuspend(playTaskHandle);
	while (TRUE) {
			/*	&& xSemaphoreTake(yellowLigthlearningSignal, portMAX_DELAY) == pdTRUE

				&& xSemaphoreTake(greenLigthlearningSignal, portMAX_DELAY) == pdTRUE) {*/
			printf("Play task tiene el mutex\r\n");
			gpioWrite(LED1, ON);
			vTaskDelay(totalRedTicks);
			printf("totalRedTicks: ", totalRedTicks);
			printf("%u\r\n", totalRedTicks);
			gpioWrite(LED1, OFF);

			vTaskSuspend(playTaskHandle);
			vTaskResume(ligthRedTaskHandle);
			vTaskDelayUntil(&initTime, 50 / portTICK_RATE_MS);
	}
}

