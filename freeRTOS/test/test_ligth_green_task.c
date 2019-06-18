#include "unity.h"
#include "ligth_green_task.h"
#include "mock_FreeRtos_test.h"
#include "mock_sapi_test.h"
#include "fake_data.h"
#include "commons.h"

static Message ligthGreenTaskMessage;
static xQueueHandle bufferMock;

void test_debe_encolar_cuando_se_prenda_la_luz_verde() {

	xSemaphoreTake_ExpectAndReturn(xsGreenLigthOn, portMAX_DELAY, pdTRUE);
	gpioRead_ExpectAndReturn(GREEN_LED_PORT, 1);
	xQueueSend_IgnoreAndReturn(1);
	xSemaphoreTake_ExpectAndReturn(xsGreenLightOff, portMAX_DELAY, pdFALSE);

	Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);

	TEST_ASSERT_EQUAL(GREEN_LED, message.Led);
	TEST_ASSERT_EQUAL(LED_ON, message.Status);

}

void test_debe_encolar_cuando_se_apaga_la_luz_verde() {

	xSemaphoreTake_ExpectAndReturn(xsGreenLigthOn, portMAX_DELAY, pdFALSE);

	xSemaphoreTake_ExpectAndReturn(xsGreenLightOff, portMAX_DELAY, pdTRUE);
	gpioRead_ExpectAndReturn(GREEN_LED_PORT, 0);
	xQueueSend_IgnoreAndReturn(1);

	Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);

	TEST_ASSERT_EQUAL(GREEN_LED, message.Led);
	TEST_ASSERT_EQUAL(LED_OFF, message.Status);

}

void test_no_debe_hacer_nada() {

	xSemaphoreTake_ExpectAndReturn(xsGreenLigthOn, portMAX_DELAY, pdFALSE);
	xSemaphoreTake_ExpectAndReturn(xsGreenLightOff, portMAX_DELAY, pdFALSE);

	Message ligthGreenTaskMessage;
	ligthGreenTaskMessage.Led = RED_LED;
	ligthGreenTaskMessage.Status = LED_OFF;

	Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);

	TEST_ASSERT_EQUAL(RED_LED, message.Led);
	TEST_ASSERT_EQUAL(LED_OFF, message.Status);

}
