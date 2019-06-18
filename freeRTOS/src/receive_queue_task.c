#include "receive_queue_task.h"
#include  "learning.h"

static void copyMessage(Message, Message *);

void receiveQueueTask(void * a) {
	xQueueHandle buffer = *(xQueueHandle *) a;
	Message sendingMessage;
	static Message oldMessage;
	while (1) {
		if (xQueueReceive(buffer, &sendingMessage, portMAX_DELAY)) {
			decideAction(sendingMessage, oldMessage);
			copyMessage(sendingMessage, &oldMessage);
			vTaskDelay(1 / portTICK_RATE_MS);
		}
	}
}

static void copyMessage(Message src, Message * dst) {
	dst->Led = src.Led;
	dst->Status = src.Status;
	dst->Time = src.Time;
}

