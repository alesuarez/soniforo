#include "debounce_fsm.h"
#include "key_service.h"

#define DEBOUNCE_DEFAULT_TIME 40

void initDebounceFsm(debounceData_t *dataStruct, gpioMap_t key) {
	dataStruct->key = key;
	dataStruct->state = BUTTON_UP_STATE;
	return;
}

bool_t getDebounceFsm(debounceData_t *ptrDataStruct) {
	bool_t isButtonPress = FALSE;

	switch (ptrDataStruct->state) {

	case BUTTON_UP_STATE:
		if (isPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_FALLING_STATE;

		}
		break;

	case BUTTON_FALLING_STATE:
		if (isPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_DOWN_STATE;
		} else {
			ptrDataStruct->state = BUTTON_UP_STATE;
		}
		break;

	case BUTTON_DOWN_STATE:
		if (notPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_RISING_STATE;
		}
		isButtonPress = TRUE;
		break;

	case BUTTON_RISING_STATE:
		if (notPress(ptrDataStruct->key)) {
			ptrDataStruct->state = BUTTON_UP_STATE;
		} else {
			ptrDataStruct->state = BUTTON_DOWN_STATE;
		}
		break;

	default:
		ptrDataStruct->state = BUTTON_UP_STATE;
		break;
	}

	return isButtonPress;
}
