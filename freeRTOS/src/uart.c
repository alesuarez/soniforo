#include "uart.h"

int sendUart(char * request,char * response) {
	/*uint8_t retValue = 0;

	debugPrintString(">>>> Enviando ");
	debugPrintlnString(&request);

	consolePrintString(&request);

	retValue = waitForReceiveStringOrTimeoutBlocking( ESP01_UART, &response, 4, 5000);

	if (retValue) {
		debugPrintString(">>>>    Exito al enviar : ");
		debugPrintlnString(&request);
	} else {
		debugPrintString(">>>>    Error al enviar : ");
		debugPrintlnString(&response);
		return retValue;
	}
*/
	return 1;
}

