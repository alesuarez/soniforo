#include "unity.h"
#include "cfg_warng_devices.h"
#include "mock_FreeRtos_test.h"
#include "mock_sapi_test.h"
#include "mock_uart.h"
#include "fake_data.h"

void test_configuracion_Esp_correcta() {

	sendUart_ExpectAndReturn("AT\r\n", "AT\r\n", 1);
	sendUart_ExpectAndReturn("AT+RST\r\n", "AT+RST\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWMODE=1\r\n", "CWMODE=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPMUX=1\r\n", "CIPMUX=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPDINFO=1\r\n", "CIPDINFO=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWAUTOCONN=0\r\n", "CWAUTOCONN=0\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWDHCP=1,1\r\n", "CWDHCP=1,1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPSTATUS?\r\n", "STATUS:5\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWMODE=2\r\n", "CWMODE=2\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWDHCP=0,1\r\n", "OK\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPSTART=3,\"UDP\",\"0\",0,4096,2\r\n", "3,CONNECT\r\n", 1);
	vTaskDelay_Ignore();

	vTaskResume_Expect(ligthRedTaskHandle);
	vTaskResume_Expect(ligthYellowTaskHandle);
	vTaskResume_Expect(ligthGreenTaskHandle);
	vTaskSuspend_Expect(blinkLedConfigurationTaskHandle);
	gpioWrite_ExpectAndReturn(LED3, ON, 1);
	vTaskDelete_Expect(esp01TaskHandle);

	esp01Task(NULL);
}

void test_configuracion_Esp_incorrecta() {

	sendUart_ExpectAndReturn("AT\r\n", "AT\r\n", 1);
	sendUart_ExpectAndReturn("AT+RST\r\n", "AT+RST\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWMODE=1\r\n", "CWMODE=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPMUX=1\r\n", "CIPMUX=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPDINFO=1\r\n", "CIPDINFO=1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWAUTOCONN=0\r\n", "CWAUTOCONN=0\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWDHCP=1,1\r\n", "CWDHCP=1,1\r\n", 1);
	sendUart_ExpectAndReturn("AT+CIPSTATUS?\r\n", "STATUS:5\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWMODE=2\r\n", "CWMODE=2\r\n", 1);
	sendUart_ExpectAndReturn("AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);
	sendUart_ExpectAndReturn("AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);
	sendUart_ExpectAndReturn("AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);
	sendUart_ExpectAndReturn("AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);

	gpioWrite_ExpectAndReturn(LED1, ON, 1);
	gpioWrite_ExpectAndReturn(LED2, ON, 1);
	gpioWrite_ExpectAndReturn(LED3, ON, 1);

	vTaskDelay_Ignore();

	vTaskResume_Expect(ligthRedTaskHandle);
	vTaskResume_Expect(ligthYellowTaskHandle);
	vTaskResume_Expect(ligthGreenTaskHandle);

	vTaskSuspend_Expect(blinkLedConfigurationTaskHandle);
	gpioWrite_ExpectAndReturn(LED3, ON, 1);

	vTaskDelete_Expect(esp01TaskHandle);

	esp01Task(NULL);

}
