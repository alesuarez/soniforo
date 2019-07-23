#ifndef FREERTOS_INC_COMMONS_H_
#define FREERTOS_INC_COMMONS_H_
#include "sapi.h"

#define ESP01_UART 				UART_232
#define DEFAULT_BAUD_RATE 		115200
#define UART_SIZE_BUFFER        104

#define RED_LED_PORT			GPIO0
#define YELLOW_LED_PORT			GPIO1
#define GREEN_LED_PORT 			GPIO2
#define isHigh 					gpioRead


typedef enum {
	LED_ON, LED_OFF
} led_status_t;

typedef enum {
	RED_LED, YELLOW_LED, GREEN_LED
} led_name_t;

typedef enum {
	INIT,
	CONFIGURING,
	LEARNING,
	LEARNING_WAITING_GREEN_LIGHT,
	LEARNING_WAITING_RED_LIGHT,
	RUNNING
} system_general_status_t;

typedef struct  {
	led_name_t Led;
	led_status_t Status;
	int32_t Time;
} message_t;



#endif /* FREERTOS_INC_COMMONS_H_ */
