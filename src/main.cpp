#include "FreeRTOS.h"
#include "portable.h"
#include "projdefs.h"
#include "task.h"

static void test_task(void* pvParams) {
    (void)pvParams;

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

int main(void)
{
    // Create RTOS tasks
    xTaskCreate(test_task, "test_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    // Should never get here
    while (1) {
    }

    return 0;
}
