#include "build/temp/_test_cfg_warng_devices.c"
#include "fake_data.h"
#include "mock_uart.h"
#include "mock_sapi_test.h"
#include "mock_FreeRtos_test.h"
#include "cfg_warng_devices.h"
#include "unity.h"




void test_configuracion_Esp_correcta() {



 sendUart_CMockExpectAndReturn(11, "AT\r\n", "AT\r\n", 1);

 sendUart_CMockExpectAndReturn(12, "AT+RST\r\n", "AT+RST\r\n", 1);

 sendUart_CMockExpectAndReturn(13, "AT+CWMODE=1\r\n", "CWMODE=1\r\n", 1);

 sendUart_CMockExpectAndReturn(14, "AT+CIPMUX=1\r\n", "CIPMUX=1\r\n", 1);

 sendUart_CMockExpectAndReturn(15, "AT+CIPDINFO=1\r\n", "CIPDINFO=1\r\n", 1);

 sendUart_CMockExpectAndReturn(16, "AT+CWAUTOCONN=0\r\n", "CWAUTOCONN=0\r\n", 1);

 sendUart_CMockExpectAndReturn(17, "AT+CWDHCP=1,1\r\n", "CWDHCP=1,1\r\n", 1);

 sendUart_CMockExpectAndReturn(18, "AT+CIPSTATUS?\r\n", "STATUS:5\r\n", 1);

 sendUart_CMockExpectAndReturn(19, "AT+CWMODE=2\r\n", "CWMODE=2\r\n", 1);

 sendUart_CMockExpectAndReturn(20, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 1);

 sendUart_CMockExpectAndReturn(21, "AT+CWDHCP=0,1\r\n", "OK\r\n", 1);

 sendUart_CMockExpectAndReturn(22, "AT+CIPSTART=3,\"UDP\",\"0\",0,4096,2\r\n", "3,CONNECT\r\n", 1);

 vTaskDelay_CMockIgnore();



 vTaskResume_CMockExpect(25, ligthRedTaskHandle);

 vTaskResume_CMockExpect(26, ligthYellowTaskHandle);

 vTaskResume_CMockExpect(27, ligthGreenTaskHandle);

 vTaskSuspend_CMockExpect(28, blinkLedConfigurationTaskHandle);

 gpioWrite_CMockExpectAndReturn(29, LED3, 1, 1);

 vTaskDelete_CMockExpect(30, esp01TaskHandle);



 esp01Task(

          ((void *)0)

              );



}
