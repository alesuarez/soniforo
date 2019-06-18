#include "build/temp/_test_ligth_green_task.c"
#include "commons.h"
#include "fake_data.h"
#include "mock_sapi_test.h"
#include "mock_FreeRtos_test.h"
#include "ligth_green_task.h"
#include "unity.h"


static Message ligthGreenTaskMessage;

static QueueHandle_t bufferMock;



void test_debe_encolar_cuando_se_prenda_la_luz_verde() {



 xSemaphoreTake_CMockExpectAndReturn(13, xsGreenLigthOn, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 1 ));

 gpioRead_CMockExpectAndReturn(14, GPIO2, 1);

 xQueueSend_CMockIgnoreAndReturn(15, 1);

 xSemaphoreTake_CMockExpectAndReturn(16, xsGreenLightOff, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 0 ));



 Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);



 UnityAssertEqualNumber((UNITY_INT)((GREEN_LED)), (UNITY_INT)((message.Led)), (

((void *)0)

), (UNITY_UINT)(20), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((LED_ON)), (UNITY_INT)((message.Status)), (

((void *)0)

), (UNITY_UINT)(21), UNITY_DISPLAY_STYLE_INT);



}



void test_debe_encolar_cuando_se_apaga_la_luz_verde() {



 xSemaphoreTake_CMockExpectAndReturn(27, xsGreenLigthOn, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 0 ));



 xSemaphoreTake_CMockExpectAndReturn(29, xsGreenLightOff, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 1 ));

 gpioRead_CMockExpectAndReturn(30, GPIO2, 0);

 xQueueSend_CMockIgnoreAndReturn(31, 1);



 Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);



 UnityAssertEqualNumber((UNITY_INT)((GREEN_LED)), (UNITY_INT)((message.Led)), (

((void *)0)

), (UNITY_UINT)(35), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((LED_OFF)), (UNITY_INT)((message.Status)), (

((void *)0)

), (UNITY_UINT)(36), UNITY_DISPLAY_STYLE_INT);



}



void test_no_debe_hacer_nada() {



 xSemaphoreTake_CMockExpectAndReturn(42, xsGreenLigthOn, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 0 ));

 xSemaphoreTake_CMockExpectAndReturn(43, xsGreenLightOff, ( TickType_t ) 0xffffffffUL, ( ( BaseType_t ) 0 ));



 Message ligthGreenTaskMessage;

 ligthGreenTaskMessage.Led = RED_LED;

 ligthGreenTaskMessage.Status = LED_OFF;



 Message message = processLigthGreen(ligthGreenTaskMessage, bufferMock);



 UnityAssertEqualNumber((UNITY_INT)((RED_LED)), (UNITY_INT)((message.Led)), (

((void *)0)

), (UNITY_UINT)(51), UNITY_DISPLAY_STYLE_INT);

 UnityAssertEqualNumber((UNITY_INT)((LED_OFF)), (UNITY_INT)((message.Status)), (

((void *)0)

), (UNITY_UINT)(52), UNITY_DISPLAY_STYLE_INT);



}
