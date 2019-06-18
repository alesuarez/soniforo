#include "build/temp/_test_learning.c"
#include "learning.h"
#include "fake_data.h"
#include "mock_uart.h"
#include "mock_FreeRtos_test.h"
#include "unity.h"




void test_puede_cruzar_la_calle() {

 Message mensajeActual;

 mensajeActual.Led = GREEN_LED;

 Message mensajeAnterior;

 mensajeAnterior.Led = YELLOW_LED;



 vTaskSuspend_CMockExpect(14, sendStatusToEthernetHandle);

 sendTextUart_CMockExpectAndReturn(15, "Cruzar\r\n", 1);

 vTaskResume_CMockExpect(16, sendStatusToEthernetHandle);

 decideAction(mensajeActual, mensajeAnterior);

}



void test_tiene_que_apurar_el_paso() {

 Message mensajeActual;

 mensajeActual.Led = YELLOW_LED;

 Message mensajeAnterior;

 mensajeAnterior.Led = GREEN_LED;



 vTaskSuspend_CMockExpect(26, sendStatusToEthernetHandle);

 sendTextUart_CMockExpectAndReturn(27, "Apurate\r\n", 1);

 vTaskResume_CMockExpect(28, sendStatusToEthernetHandle);

 decideAction(mensajeActual, mensajeAnterior);

}



void test_culquier_estado_debe_esperar() {

 Message mensajeActual;

 mensajeActual.Led = YELLOW_LED;

 Message mensajeAnterior;

 mensajeAnterior.Led = RED_LED;



 vTaskSuspend_CMockExpect(38, sendStatusToEthernetHandle);

 sendTextUart_CMockExpectAndReturn(39, "Esperar\r\n", 1);

 decideAction(mensajeActual, mensajeAnterior);

}
