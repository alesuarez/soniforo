#include "peripheral_driver.h"
#include "sapi.h"

#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
//#include "event_framework.h"
//#include "event.h"

#define CH0						0
#define CH1						1
#define CH2						2
#define GPIO_3					3
#define PIN_0					0
#define PIN_3					3
#define PIN_4					4

#define ISR_PRIORITY			5

//extern module_t * lightsModule;

void IRQ_init() {
	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(0, 0, 4); 				//Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH0); 	//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH0);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH0);

	NVIC_SetPriority(PIN_INT0_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT0_IRQn);

	Chip_PININT_Init(LPC_GPIO_PIN_INT);

	Chip_SCU_GPIOIntPinSel(1, 0, 8); 				//Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH1); 	//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH1);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH1);

	NVIC_SetPriority(PIN_INT1_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT1_IRQn);

	Chip_SCU_GPIOIntPinSel(2, 0, 9); 				//Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH2); 	//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH2);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH2);

	NVIC_SetPriority(PIN_INT2_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT2_IRQn);

	Chip_SCU_GPIOIntPinSel(3, 1, 9); 				//Mapeo del pin donde ocurrirá el evento y

	Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT, PININTCH3); 	//Se configura el canal
	Chip_PININT_EnableIntLow(LPC_GPIO_PIN_INT, PININTCH3);
	Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT, PININTCH3);

	NVIC_SetPriority(PIN_INT3_IRQn, 5);
	NVIC_EnableIRQ(PIN_INT3_IRQn);
}

void GPIO0_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_PULSADO, 0);
		/*evn.value = 0;
		evn.signal = SIG_BOTON_PULSADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH0) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH0); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_LIBERADO, 0);
		/*evn.value = 0;
		evn.signal = SIG_BOTON_LIBERADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO1_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
	//	xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_PULSADO, 1);
		/*evn.value = 1;
		evn.signal = SIG_BOTON_PULSADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH1) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH1); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_LIBERADO, 1);
		/*evn.value = 1;
		evn.signal = SIG_BOTON_LIBERADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO2_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_PULSADO, 2);
		/*evn.value = 2;
		evn.signal = SIG_BOTON_PULSADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH2) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH2); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_LIBERADO, 2);
		/*evn.value = 2;
		evn.signal = SIG_BOTON_LIBERADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

void GPIO3_IRQHandler(void) {
	portBASE_TYPE xSwitchRequired = pdFALSE;

	if (Chip_PININT_GetFallStates(LPC_GPIO_PIN_INT) & PININTCH3) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH3); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_PULSADO, 3);
		/*evn.value = 3;
		evn.signal = SIG_BOTON_PULSADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	if (Chip_PININT_GetRiseStates(LPC_GPIO_PIN_INT) & PININTCH3) { //Verificamos que la interrupción es la esperada
		Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT, PININTCH3); //Borramos el flag de interrupción
		//xSwitchRequired = putEventFromISR(buttonsModule, SIG_BOTON_LIBERADO, 3);
		/*evn.value = 3;
		evn.signal = SIG_BOTON_LIBERADO;
		evn.receptor =	buttonsModule;
		xQueueSendFromISR( queEvento, &evn, &xSwitchRequired );*/
	}

	portEND_SWITCHING_ISR(xSwitchRequired); //Terminar con taskYIELD_FROM_ISR (&xSwitchRequired);
}

