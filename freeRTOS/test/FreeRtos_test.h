#include <stdint.h>

#define configTICK_RATE_HZ	( ( TickType_t ) 1000 )
#define portTICK_PERIOD_MS	( ( TickType_t ) 1000 / configTICK_RATE_HZ )
#define portTICK_RATE_MS portTICK_PERIOD_MS
typedef uint32_t TickType_t;
typedef void * TaskHandle_t;
typedef void * QueueHandle_t;
typedef QueueHandle_t SemaphoreHandle_t;

void vTaskDelay( TickType_t xTicksToDelay );
void vTaskResume( TaskHandle_t xTaskToResume );
void vTaskSuspend( TaskHandle_t xTaskToSuspend );
void vTaskDelete( TaskHandle_t xTaskToDelete );
