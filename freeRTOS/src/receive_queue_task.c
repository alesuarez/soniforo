#include "receive_queue_task.h"
#include  "learding.h"

static void copyMessage(struct Message, struct Message *);

void receiveQueueTask(void * a) {
	xQueueHandle buffer = *(xQueueHandle *) a;
	struct Message sendingMessage;
	static struct Message oldMessage;
	while (1) {
		if (xQueueReceive(buffer, &sendingMessage, portMAX_DELAY)) {
			decideAction(sendingMessage, oldMessage);
			copyMessage(sendingMessage, &oldMessage);
			vTaskDelay(1 / portTICK_RATE_MS);
		}
	}
}

static void copyMessage(struct Message src, struct Message * dst) {
	dst->Led = src.Led;
	dst->Status = src.Status;
	dst->Time = src.Time;
}

