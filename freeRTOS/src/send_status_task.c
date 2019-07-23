#include "send_status_task.h"


void sendStatusToEsp01Task(void * a) {
	while (1) {
		//debugPrintlnString("Cruzar\r\n");
		//sendCmd(CMD_CIPSEND);
		//consolePrintString("Cruzar\r\n");
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}
