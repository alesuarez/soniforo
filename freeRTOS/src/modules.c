#include "modules.h"
#include "event_framework.h"

#define MAX_MODULES 10
module_t modules[MAX_MODULES];
int moduleIndex = 0;

module_t * registerModule(fsm_ptr eventHandler) {

	if (moduleIndex == MAX_MODULES) {
		return ((void *) 0);
	}

	module_t * newModule = &modules[moduleIndex];
	newModule->eventHandler = eventHandler;
	moduleIndex++;

	return newModule;
}

void initAllModules() {
	event_t evn;
	for(int i = 0; i < moduleIndex; i++)  {
		evn.signal = SIG_INIT;
		evn.receptor = &modules[i];
		fsm_ptr eventHandler = (evn.receptor)->eventHandler;
		eventHandler(&evn);
	}
}

void initStatusModule() {
	event_t evn;
	evn.signal = SIG_INIT;
	evn.receptor = &modules[0];
	fsm_ptr eventHandler = (evn.receptor)->eventHandler;
	eventHandler(&evn);
}



