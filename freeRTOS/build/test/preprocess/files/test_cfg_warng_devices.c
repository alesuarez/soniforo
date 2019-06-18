#include "build/temp/_test_cfg_warng_devices.c"
#include "fake_data.h"
#include "mock_uart.h"
#include "mock_sapi_test.h"
#include "mock_FreeRtos_test.h"
#include "cfg_warng_devices.h"
#include "unity.h"


void test_configuracion_Esp_correcta() {



 sendUart_CMockExpectAndReturn(10, "AT\r\n", "AT\r\n", 1);

 sendUart_CMockExpectAndReturn(11, "AT+RST\r\n", "AT+RST\r\n", 1);

 sendUart_CMockExpectAndReturn(12, "AT+CWMODE=1\r\n", "CWMODE=1\r\n", 1);

 sendUart_CMockExpectAndReturn(13, "AT+CIPMUX=1\r\n", "CIPMUX=1\r\n", 1);

 sendUart_CMockExpectAndReturn(14, "AT+CIPDINFO=1\r\n", "CIPDINFO=1\r\n", 1);

 sendUart_CMockExpectAndReturn(15, "AT+CWAUTOCONN=0\r\n", "CWAUTOCONN=0\r\n", 1);

 sendUart_CMockExpectAndReturn(16, "AT+CWDHCP=1,1\r\n", "CWDHCP=1,1\r\n", 1);

 sendUart_CMockExpectAndReturn(17, "AT+CIPSTATUS?\r\n", "STATUS:5\r\n", 1);

 sendUart_CMockExpectAndReturn(18, "AT+CWMODE=2\r\n", "CWMODE=2\r\n", 1);

 sendUart_CMockExpectAndReturn(19, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 1);

 sendUart_CMockExpectAndReturn(20, "AT+CWDHCP=0,1\r\n", "OK\r\n", 1);

 sendUart_CMockExpectAndReturn(21, "AT+CIPSTART=3,\"UDP\",\"0\",0,4096,2\r\n", "3,CONNECT\r\n", 1);

 vTaskDelay_CMockIgnore();



 vTaskResume_CMockExpect(24, ligthRedTaskHandle);

 vTaskResume_CMockExpect(25, ligthYellowTaskHandle);

 vTaskResume_CMockExpect(26, ligthGreenTaskHandle);

 vTaskSuspend_CMockExpect(27, blinkLedConfigurationTaskHandle);

 gpioWrite_CMockExpectAndReturn(28, LED3, 1, 1);

 vTaskDelete_CMockExpect(29, esp01TaskHandle);



 esp01Task(

          ((void *)0)

              );

}



void test_configuracion_Esp_incorrecta() {



 sendUart_CMockExpectAndReturn(36, "AT\r\n", "AT\r\n", 1);

 sendUart_CMockExpectAndReturn(37, "AT+RST\r\n", "AT+RST\r\n", 1);

 sendUart_CMockExpectAndReturn(38, "AT+CWMODE=1\r\n", "CWMODE=1\r\n", 1);

 sendUart_CMockExpectAndReturn(39, "AT+CIPMUX=1\r\n", "CIPMUX=1\r\n", 1);

 sendUart_CMockExpectAndReturn(40, "AT+CIPDINFO=1\r\n", "CIPDINFO=1\r\n", 1);

 sendUart_CMockExpectAndReturn(41, "AT+CWAUTOCONN=0\r\n", "CWAUTOCONN=0\r\n", 1);

 sendUart_CMockExpectAndReturn(42, "AT+CWDHCP=1,1\r\n", "CWDHCP=1,1\r\n", 1);

 sendUart_CMockExpectAndReturn(43, "AT+CIPSTATUS?\r\n", "STATUS:5\r\n", 1);

 sendUart_CMockExpectAndReturn(44, "AT+CWMODE=2\r\n", "CWMODE=2\r\n", 1);

 sendUart_CMockExpectAndReturn(45, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);

 sendUart_CMockExpectAndReturn(46, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);

 sendUart_CMockExpectAndReturn(47, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);

 sendUart_CMockExpectAndReturn(48, "AT+CWSAP=\"Soniforo_CIAA\",\"\",8,0\r\n", "OK\r\n", 0);



 gpioWrite_CMockExpectAndReturn(50, LED1, 1, 1);

 gpioWrite_CMockExpectAndReturn(51, LED2, 1, 1);

 gpioWrite_CMockExpectAndReturn(52, LED3, 1, 1);



 vTaskDelay_CMockIgnore();



 vTaskResume_CMockExpect(56, ligthRedTaskHandle);

 vTaskResume_CMockExpect(57, ligthYellowTaskHandle);

 vTaskResume_CMockExpect(58, ligthGreenTaskHandle);



 vTaskSuspend_CMockExpect(60, blinkLedConfigurationTaskHandle);

 gpioWrite_CMockExpectAndReturn(61, LED3, 1, 1);



 vTaskDelete_CMockExpect(63, esp01TaskHandle);



 esp01Task(

          ((void *)0)

              );



}
