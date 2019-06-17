









typedef uint32_t TickType_t;

typedef void * TaskHandle_t;

typedef void * QueueHandle_t;

typedef QueueHandle_t SemaphoreHandle_t;



void vTaskDelay( TickType_t xTicksToDelay );

void vTaskResume( TaskHandle_t xTaskToResume );

void vTaskSuspend( TaskHandle_t xTaskToSuspend );

void vTaskDelete( TaskHandle_t xTaskToDelete );
