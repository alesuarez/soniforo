
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

DEBUG_PRINT_ENABLE
CONSOLE_PRINT_ENABLE



int main(void) {

	// Inicializar la placa
	boardConfig();
	// Configura la UART USB a 115200 baudios
	uartConfig(UART_USB, 115200);
	// Envia un mensaje de bienvenida.

	gpioWrite(LED3, ON);





	vTaskStartScheduler();

	while ( TRUE) {
		// Si cae en este while 1 significa que no pudo iniciar el scheduler
		gpioWrite(LED3, OFF);
	}

	return 0;
}



