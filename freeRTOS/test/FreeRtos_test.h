#include <stdint.h>

#define configTICK_RATE_HZ	( ( TickType_t ) 1000 )
#define portTICK_PERIOD_MS	( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICK_RATE_MS portTICK_PERIOD_MS
#define xQueueHandle QueueHandle_t
#define portTickType TickType_t
#define portMAX_DELAY ( TickType_t ) 0xffffffffUL
#define pdTRUE			( ( BaseType_t ) 1 )
#define pdFALSE			( ( BaseType_t ) 0 )

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
