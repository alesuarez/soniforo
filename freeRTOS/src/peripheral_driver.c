#include "peripheral_driver.h"
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "event_framework.h"
#include "queue.h"
#include "sapi.h"
#include "event.h"
#include "soniforo.h"
#include "uart_task.h"
#include "sound.h"

#define CH0						0
#define CH1						1
#define CH2						2
#define GPIO_3					3
#define PIN_0					0
#define PIN_3					3
#define PIN_4					4
#define ISR_PRIORITY			5

uint8_t transmiterCounter;
uint16_t signalPower = 1;
uint16_t lapse = 10000;

void IRQ_init() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(0, 3, 3); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH0); //Se configura para que el
	NVIC_SetPriority(PIN_INT0_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT0_IRQn);

	Chip_SCU_GPIOIntPinSel(1, 5, 15); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH1); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1); //Se configura para que el
	NVIC_SetPriority(PIN_INT1_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	Chip_SCU_GPIOIntPinSel(2, 3, 5); //Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH2); //Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH2); //Se configura para que el
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH2); //Se configura para que el
	NVIC_SetPriority(PIN_INT2_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT2_IRQn);
}

void GPIO0_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_ON, RED_LED); // OPTOSENSOR
		//xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, RED_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_OFF, RED_LED);
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, RED_LED);// OPTOSENSOR
		//xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_ON, RED_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_ON, RED_LED);
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO1_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
		//xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, YELLOW_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_OFF, YELLOW_LED);
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_ON, YELLOW_LED);// OPTOSENSOR
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, YELLOW_LED);// OPTOSENSOR
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_ON, YELLOW_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_ON, YELLOW_LED);
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO2_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_ON, GREEN_LED);// OPTOSENSOR
		//xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, GREEN_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_OFF, GREEN_LED);
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_OFF, GREEN_LED);// OPTOSENSOR
		//xSwitchRequired = putLightEventFromISR(lightsModule, SIG_LIGHT_ON, GREEN_LED);
		//xSwitchRequired = putLightEventFromISR(debounceModule, SIG_LIGHT_ON, GREEN_LED);
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void timer0Init(uint32_t MatchCount){
	Chip_TIMER_Init(LPC_TIMER0);
	Chip_TIMER_SetMatch(LPC_TIMER0, 0, MatchCount);
	Chip_TIMER_ResetOnMatchEnable(LPC_TIMER0, 0);
	Chip_TIMER_MatchEnableInt(LPC_TIMER0, 0);
	Chip_TIMER_Enable(LPC_TIMER0);
}


void TIMER0_IRQHandler(void){
	int32_t tmp;
	if (Chip_TIMER_MatchPending(LPC_TIMER0, 0)) {
		static uint16_t indice = 0;
		if (indice < 1716) {
			//taskENTER_CRITICAL();
			Chip_DAC_UpdateValue(LPC_DAC, rawData[indice]/(signalPower));	// Mitad para no saturar line-in
			//taskEXIT_CRITICAL();

		} else if (indice > 1716 && indice < lapse) {
			Chip_DAC_UpdateValue(LPC_DAC,0);	// Mitad para no saturar line-in
		}
		if (indice > 10000) {
			indice=0;
		}
		indice++;
		Chip_TIMER_ClearMatch(LPC_TIMER0, 0);
	}
}

void setSignalPower(uint16_t newSignalPower) {
	signalPower = newSignalPower;
}

void setLapse(uint16_t newLapse) {
	lapse = newLapse;
}

void UART_init() {
	uartConfig(UART_USB, 115200);
	uartConfig(UART_232, 115200);

	uartCallbackSet(UART_USB, UART_RECEIVE, usbRX_int_handler, NULL);
	uartCallbackSet(UART_232, UART_RECEIVE, rs232RX_int_handler, NULL);

	uartInterrupt(UART_USB, true);
	uartInterrupt(UART_232, true);
}

void usbRX_int_handler(void * p) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    uint8_t receive = uartRxRead(UART_USB);

    xQueueSendFromISR(usbRxQueue, &receive, &xHigherPriorityTaskWoken );

    if (xHigherPriorityTaskWoken != pdFALSE) {
    	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
}

void rs232RX_int_handler(void * p) {
	static BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    uint8_t receive = uartRxRead(UART_232);

    xQueueSendFromISR(rs232RxQueue, &receive, &xHigherPriorityTaskWoken );

    if (xHigherPriorityTaskWoken != pdFALSE) {
    	portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
    }
}



