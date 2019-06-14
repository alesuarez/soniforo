#include "esp_driver.h"

bool_t sendCmd(CommandEsp8266_t cmd) {
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
