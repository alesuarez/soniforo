#include "callbacks_functions.h"
#include "event_framework.h"
#include "event.h"
#include "soniforo.h"

static void debounceCallback(led_name_t);

void initConfigurationCallback() {
	putEvent(statusModule, SIG_CONFIGURING_INIT);
}

void redLightCallback() {

}

void yellowLightCallback() {

}

void greenLightCallback() {

}

void debounceRedLightCallback(TimerHandle_t xTimer) {
	debounceCallback(RED_LED);
}

void debounceYellowLightCallback(TimerHandle_t xTimer) {
	debounceCallback(YELLOW_LED);
}

void debounceGreenLightCallback(TimerHandle_t xTimer) {
	debounceCallback(GREEN_LED);
}
static void debounceCallback(led_name_t ledName) {
	putLightEvent(debounceModule, SIG_TIMEOUT, ledName);
}
