#include "FreeRTOS.h"
#include "task.h"
#include "logging.h"
#include "encoder.h"

static void test_task(void *pvParams)
{
    (void)pvParams;

    Encoder encoder(Encoder::CHANNEL_0);

    float angle_deg = 0;
    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(600));

        encoder.read(&angle_deg);
        logger_println("Main", "Angle %f", angle_deg);
    }
}

int main(void)
{
    logger_init();

    // Create RTOS tasks
    xTaskCreate(test_task, "test_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    // Should never get here
    while (1)
    {
    }

    return 0;
}
