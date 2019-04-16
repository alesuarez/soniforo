#ifndef APP_INC_DEBOUNCE_FSM_H_
#define APP_INC_DEBOUNCE_FSM_H_

#include "sapi.h"

typedef enum {
	BUTTON_UP_STATE,
	BUTTON_FALLING_STATE,
	BUTTON_DOWN_STATE,
	BUTTON_RISING_STATE
} DebounceFsmState;

typedef struct{
	gpioMap_t key;
	DebounceFsmState state;
	delay_t delay;
} debounceData_t;

void initDebounceFsm(debounceData_t * dataStruct, gpioMap_t key);
bool_t getDebounceFsm(debounceData_t * ptrDataStruct, gpioMap_t pressedKey);

#endif
