#ifndef FREERTOS_INC_MODULES_H_
#define FREERTOS_INC_MODULES_H_
#include "commons.h"

typedef struct module_t module_t;
typedef struct event_t event_t;

typedef void (*fsm_ptr)(event_t *);

struct module_t {
	fsm_ptr eventHandler;
};

struct event_t {
	module_t * receptor;
	int signal;
	led_name_t ledName;
};

module_t * registerModule(fsm_ptr eventHandler);
void initAllModules();
void initStatusModule();

#endif /* FREERTOS_INC_MODULES_H_ */
