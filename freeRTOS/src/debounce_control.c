#include "debounce_control.h"
#include "event.h"
#include "sapi.h"
#include "soniforo.h"

#define notPress gpioRead

//#define isPress (!gpioRead) todo: remplace

typedef enum {
	ON_STATE,
	GOING_OUT_STATE,
	OFF_STATE,
	TURNING_ON_STATE
} DebounceFsmState;

typedef struct{
	gpioMap_t lightPort;
	DebounceFsmState state;
	bool_t isFilter;
} debounceData_t;

debounceData_t debounceDatas[MAX_LIGHTS];
char debounceTimeArray[10][MAX_LIGHTS];

static void initButtonsModule();
static void debouncefsm(debounceData_t *, event_t *) ;
static void debounceInit(debounceData_t *, gpioMap_t);

void debounceHandler(event_t * evn) {
	switch (evn->signal) {
		case SIG_INIT:
			initButtonsModule();
			break;
		case SIG_TIMEOUT:
			debouncefsm(&debounceDatas[evn->ledName], evn);
		  	xTimerStop(lightDebounceTimerHandles[evn->ledName], 0);
			break;
		case SIG_LIGHT_ON:
			debouncefsm(&debounceDatas[evn->ledName], evn);
			xTimerStart(lightDebounceTimerHandles[evn->ledName], 0);
			break;
		case SIG_LIGHT_OFF:
			debouncefsm(&debounceDatas[evn->ledName], evn);
			xTimerStart(lightDebounceTimerHandles[evn->ledName], 0);
		}
}

static void initButtonsModule() {
	debounceInit(&debounceDatas[RED_LED], RED_LED_PORT);
	debounceInit(&debounceDatas[YELLOW_LED], YELLOW_LED_PORT);
	debounceInit(&debounceDatas[GREEN_LED], GREEN_LED_PORT);
}

static void debounceInit(debounceData_t * debounceData, gpioMap_t lightPort) {
	debounceData->lightPort = lightPort;
	debounceData->state = ON_STATE;
	debounceData->isFilter = FALSE;
}

static void debouncefsm(debounceData_t * ptrDataStruct, event_t * evn) {

	switch (ptrDataStruct->state) {

		case ON_STATE:
			if (!notPress(ptrDataStruct->lightPort)) {
				ptrDataStruct->state = GOING_OUT_STATE;
			}
			break;

		case GOING_OUT_STATE:
			if (!notPress(ptrDataStruct->lightPort)) {
				ptrDataStruct->state = OFF_STATE;
				putLightEvent(lightsModule, SIG_LIGHT_ON, evn->ledName);
			} else {
				ptrDataStruct->state = ON_STATE;
			}
			break;

		case OFF_STATE:
			if (notPress(ptrDataStruct->lightPort)) {
				ptrDataStruct->state = TURNING_ON_STATE;
			}
			break;

		case TURNING_ON_STATE:
			if (notPress(ptrDataStruct->lightPort)) {
				putLightEvent(lightsModule, SIG_LIGHT_OFF, evn->ledName);
				ptrDataStruct->state = ON_STATE;
			} else {
					ptrDataStruct->state = OFF_STATE;
			}
			break;

		default:
			ptrDataStruct->state = ON_STATE;
			break;
		}
		return;
}
