#ifndef FREERTOS_INC_PERIPHERAL_DRIVER_H_
#define FREERTOS_INC_PERIPHERAL_DRIVER_H_
#include "sapi.h"

//uchar_t txBuffer[100];

void IRQ_init();
void GPIO0_IRQHandler(void);
void GPIO1_IRQHandler(void);
void GPIO2_IRQHandler(void);

void UART_init(void);
void usbRX_int_handler(void *);
void rs232RX_int_handler(void *);

void systemError();

#endif /* FREERTOS_INC_PERIPHERAL_DRIVER_H_ */
