#ifndef FREERTOS_TEST_SAPI_TEST_H_
#define FREERTOS_TEST_SAPI_TEST_H_
#include "sapi_types_test.h"


bool_t gpioWrite( gpioMap_t pin, bool_t value );
bool_t gpioRead( gpioMap_t pin );
bool_t isHigh( gpioMap_t pin );

#endif /* FREERTOS_TEST_SAPI_TEST_H_ */
