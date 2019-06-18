#ifndef FREERTOS_INC_COMMONS_H_
#define FREERTOS_INC_COMMONS_H_

#ifdef TEST
#include "FreeRtos_test.h"
#include "sapi_test.h"
#include "fake_data.h"
#else
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"

#include "task.h"
#include "semphr.h"
#include "sapi.h"
#include "driver.h"

CONSOLE_PRINT_ENABLE
DEBUG_PRINT_ENABLE

#endif



#define ESP01_UART 				UART_232
#define DEFAULT_BAUD_RATE 		115200

#define RED_LED_PORT			GPIO0
#define YELLOW_LED_PORT			GPIO1
#define GREEN_LED_PORT 			GPIO2
#define isHigh 					gpioRead



typedef enum {
	LED_ON, LED_OFF
} Led_Status;

typedef enum {
	RED_LED, YELLOW_LED, GREEN_LED
} Led_Name;

typedef struct  {
	Led_Name Led;
	Led_Status Status;
	int32_t Time;
} Message;

extern SemaphoreHandle_t xsRedLigthOn;
extern SemaphoreHandle_t xsRedLightOff;
extern SemaphoreHandle_t xsYellowLigthOn;
extern SemaphoreHandle_t xsYellowLightOff;
extern SemaphoreHandle_t xsGreenLigthOn;
extern SemaphoreHandle_t xsGreenLightOff;



extern TaskHandle_t sendStatusToEthernetHandle;
extern TaskHandle_t ligthYellowTaskHandle;
extern TaskHandle_t ligthGreenTaskHandle;
extern TaskHandle_t ligthRedTaskHandle;
extern TaskHandle_t sendTaskHandle;
extern TaskHandle_t esp01TaskHandle;
extern TaskHandle_t blinkLedConfigurationTaskHandle;

xQueueHandle sendBuffer;
xQueueHandle uartQueue;


#endif /* FREERTOS_INC_COMMONS_H_ */
