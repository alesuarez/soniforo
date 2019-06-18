#ifndef FREERTOS_INC_LIGTH_GREEN_TASK_H_
#define FREERTOS_INC_LIGTH_GREEN_TASK_H_
#include "commons.h"

#ifdef TEST
#define privada
#else
#define privada static
#endif

privada Message processLigthGreen(Message, xQueueHandle);
void ligthGreenTask(void *);

#endif /* FREERTOS_INC_LIGTH_GREEN_TASK_H_ */
