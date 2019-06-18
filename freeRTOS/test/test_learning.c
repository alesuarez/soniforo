#include "unity.h"
#include "mock_FreeRtos_test.h"
#include "mock_uart.h"
#include "fake_data.h"
#include "learning.h"


void test_puede_cruzar_la_calle() {
	Message mensajeActual;
	mensajeActual.Led = GREEN_LED;
	Message mensajeAnterior;
	mensajeAnterior.Led = YELLOW_LED;

	vTaskSuspend_Expect(sendStatusToEthernetHandle);
	sendTextUart_ExpectAndReturn("Cruzar\r\n", 1);
	vTaskResume_Expect(sendStatusToEthernetHandle);

	decideAction(mensajeActual, mensajeAnterior);
}

void test_tiene_que_apurar_el_paso() {
	Message mensajeActual;
	mensajeActual.Led = YELLOW_LED;
	Message mensajeAnterior;
	mensajeAnterior.Led = GREEN_LED;

	vTaskSuspend_Expect(sendStatusToEthernetHandle);
	sendTextUart_ExpectAndReturn("Apurate\r\n", 1);
	vTaskResume_Expect(sendStatusToEthernetHandle);

	decideAction(mensajeActual, mensajeAnterior);
}

void test_culquier_estado_debe_esperar() {
	Message mensajeActual;
	mensajeActual.Led = YELLOW_LED;
	Message mensajeAnterior;
	mensajeAnterior.Led = RED_LED;

	vTaskSuspend_Expect(sendStatusToEthernetHandle);
	sendTextUart_ExpectAndReturn("Esperar\r\n", 1);

	decideAction(mensajeActual, mensajeAnterior);
}
