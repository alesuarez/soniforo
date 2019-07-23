#include "learning_control.h"
#include "uart.h"
#include "event_framework.h"
#include "event.h"

extern module_t * statusModule;

void learningHandler( event_t * evn ) {
	switch( evn->signal ) {
		case SIG_INIT:
			break;
		case SIG_LEARNING_INIT:
			break;
		case SIG_LEARNING_WAITING_RED_LIGHT:
			break;
		case SIG_LEARNING_FINISH:
			break;
	}
}

