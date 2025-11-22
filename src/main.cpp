#include "FreeRTOS.h"
#include "task.h"
#include "logging.h"

static void test_task(void* pvParams) {
    (void)pvParams;

    int i = 0;
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));

        logger_println("Main", "Hello %d", i);
        i++;
    }
}

int main(void)
{
    logger_init();

    // Create RTOS tasks
    xTaskCreate(test_task, "test_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    // Should never get here
    while (1) {
    }

    return 0;
}
