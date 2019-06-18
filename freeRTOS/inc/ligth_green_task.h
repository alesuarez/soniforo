#ifndef FREERTOS_INC_LIGTH_GREEN_TASK_H_
#define FREERTOS_INC_LIGTH_GREEN_TASK_H_
#include "commons.h"

Message processLigthGreen(Message, xQueueHandle);
void ligthGreenTask(void *);

#endif /* FREERTOS_INC_LIGTH_GREEN_TASK_H_ */
