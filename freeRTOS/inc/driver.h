#ifndef FREERTOS_INC_DRIVER_H_
#define FREERTOS_INC_DRIVER_H_

#include "commons.h"

#define CH0						0
#define CH1						1
#define CH2						2
#define GPIO_3					3
#define PIN_0					0
#define PIN_3					3
#define PIN_4					4

#define ISR_PRIORITY			5

#define MAX_ATTEMPT				3

void IRQ_init(); 				// configuracion de las interrupciones del micro
void GPIO0_IRQHandler(void); 	// handler de la luz roja
void GPIO1_IRQHandler(void); 	// handler de la luz amarilla
void GPIO2_IRQHandler(void); 	// handler de la luz verde
void systemError();

#endif /* FREERTOS_INC_DRIVER_H_ */
