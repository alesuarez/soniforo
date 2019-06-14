#include  "learding.h"

void decideAction(struct Message new, struct Message old) {
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
