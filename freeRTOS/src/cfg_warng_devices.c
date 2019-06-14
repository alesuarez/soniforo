#include "cfg_warng_devices.h"

void esp01Task(void *p) {

	consolePrintConfigUart(ESP01_UART, DEFAULT_BAUD_RATE);
	debugPrintConfigUart(UART_USB, DEFAULT_BAUD_RATE );
	int16_t attemptsValue = 0;

	for (int i = 0; i < COMMAND_INIT_LENGHT; i++) {
		if (!sendCmd(initVector[i])) {
			vTaskDelay(2000 / portTICK_RATE_MS);
			i = i - 1 < 0 ? 0 : i -1 ;
			sendCmd(initVector[i]);

			attemptsValue++;
			if (attemptsValue > MAX_ATTEMPT ) {
				systemError();
			}
		}
		vTaskDelay(5000 / portTICK_RATE_MS);
	}

	vTaskResume(ligthRedTaskHandle);	// una vez iniciada correctamente
	vTaskResume(ligthYellowTaskHandle); // la placa inicio las tareas
	vTaskResume(ligthGreenTaskHandle);	// que atienden las luces

	vTaskSuspend(blinkLedConfigurationTaskHandle); 		// suspendo esta tarea
	gpioWrite(LED3, ON);

	vTaskDelete(esp01TaskHandle); 		// suspendo esta tarea

}
