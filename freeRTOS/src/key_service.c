#include "key_service.h"

bool_t isPress(gpioMap_t key) {
	return !gpioRead(key);
}

bool_t notPress(gpioMap_t key) {
	return gpioRead(key);
}
