#ifndef FREERTOS_INC_ESP01_DRIVE_H_
#define FREERTOS_INC_ESP01_DRIVE_H_

#include "sapi.h"

#define ESP01_UART UART_232
#define ESP01_BAUD_RATE 115200

bool_t esp01Init();
bool_t initAP();
void sendUDP();

#endif /* FREERTOS_INC_ESP01_DRIVE_H_ */
