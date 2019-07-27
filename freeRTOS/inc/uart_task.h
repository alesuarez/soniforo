#ifndef FREERTOS_INC_UART_TASK_H_
#define FREERTOS_INC_UART_TASK_H_
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"

QueueHandle_t usbRxQueue;
QueueHandle_t usbTxQueue;

QueueHandle_t rs232RxQueue;
QueueHandle_t rs232TxQueue;

//SemaphoreHandle_t xTxSemaphore;

void usbRxTask(void *);
void usbTxTask(void *);

void rs232RxTask(void *);
void rs232TxTask(void *);

#endif /* FREERTOS_INC_UART_TASK_H_ */
