#include "broadcast.h"
#include "sapi.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "timers.h"
#include "rtos_service.h"
#include "cfg_warng_devices.h"
#include "peripheral_driver.h"

#define LAPSE_HIGH 5000
#define LAPSE_LOW 10000

void broadcastHandler(event_t * evn) {

	switch (evn->signal) {
		case SIG_INIT:
			break;
		case SIG_WAIT:
			vTaskSuspend(sendStatusCrossEsp01TaskHandle);
			vTaskSuspend(sendStatusCautionEsp01TaskHandle);
			//xTimerStart(greenLightTimerHandle, 0);
			xTimerStop(redLightTimerHandle, 0);
			xTimerStop(yellowLightTimerHandle, 0);
			NVIC_DisableIRQ(TIMER0_IRQn);
			taskENTER_CRITICAL();
			setLapse(LAPSE_HIGH);
			taskEXIT_CRITICAL();
			gpioWrite(LED1, ON); //rojo
			gpioWrite(LED2, OFF);
			gpioWrite(LED3, OFF);
			break;
		case SIG_CROSS:
			xTimerStart(redLightTimerHandle, 0);
			vTaskResume(sendStatusCrossEsp01TaskHandle);
			//taskENTER_CRITICAL();
			//setLapse(LAPSE_LOW);
			//taskEXIT_CRITICAL();
			NVIC_EnableIRQ(TIMER0_IRQn);
			gpioWrite(LED1, OFF);
			gpioWrite(LED2, OFF);
			gpioWrite(LED3, ON);//verde
			break;
		case SIG_CAUTION:
			vTaskSuspend(sendStatusCrossEsp01TaskHandle);
			xTimerStop(redLightTimerHandle, 0);
			xTimerStart(yellowLightTimerHandle, 0);
			vTaskResume(sendStatusCautionEsp01TaskHandle);
			//taskENTER_CRITICAL();
			//setLapse(LAPSE_HIGH);
			//taskEXIT_CRITICAL();
			NVIC_EnableIRQ(TIMER0_IRQn);
			gpioWrite(LED1, OFF);
			gpioWrite(LED3, OFF);
			gpioWrite(LED2, ON);//amarillo
			break;
	}
}
