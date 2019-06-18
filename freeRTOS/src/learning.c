#include "learning.h"
#include "uart.h"


void decideAction(Message new, Message old) {
	// todo: In this implementation the turn off leds states were not taken into account

	vTaskSuspend(sendStatusToEthernetHandle);

	if (old.Led == YELLOW_LED && new.Led == GREEN_LED) { // el semaforo esta en verde
		sendTextUart("Cruzar\r\n");
		vTaskResume(sendStatusToEthernetHandle);
		return;
	}

	if (old.Led == GREEN_LED && new.Led == YELLOW_LED) { // el semaforo se esta por poner en rojo
		sendTextUart("Apurate\r\n");
		vTaskResume(sendStatusToEthernetHandle);
		return;
	}

	sendTextUart("Esperar\r\n"); // cualquier otro estado el sistema indica que no se puede cruzar
	return;
}
