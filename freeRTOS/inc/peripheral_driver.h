#ifndef FREERTOS_INC_PERIPHERAL_DRIVER_H_
#define FREERTOS_INC_PERIPHERAL_DRIVER_H_

void IRQ_init();
void GPIO0_IRQHandler(void);
void GPIO1_IRQHandler(void);
void GPIO2_IRQHandler(void);
void GPIO3_IRQHandler(void);

void systemError();


#endif /* FREERTOS_INC_PERIPHERAL_DRIVER_H_ */
