

typedef long BaseType_t;

typedef uint32_t TickType_t;

typedef void * TaskHandle_t;

typedef void * QueueHandle_t;

typedef QueueHandle_t SemaphoreHandle_t;



void vTaskDelay( TickType_t xTicksToDelay );

void vTaskResume( TaskHandle_t xTaskToResume );

void vTaskSuspend( TaskHandle_t xTaskToSuspend );

void vTaskDelete( TaskHandle_t xTaskToDelete );

void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement );

TickType_t xTaskGetTickCount( void );

BaseType_t xSemaphoreTake( QueueHandle_t xQueue, TickType_t xTicksToWait );

BaseType_t xQueueSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait);
