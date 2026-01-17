#include "FreeRTOS.h"
#include "task.h"
#include "logging.h"
#include "encoder.h"
#include "ecat_app.h"

static void sensors_read_task(void *pvParams)
{
    (void)pvParams;

    Encoder* enc0 = Encoder::getInstance(Encoder::CHANNEL_0);

    float angle_deg = 0;
    while (1)
    {
        enc0->fetch();

        vTaskDelay(pdMS_TO_TICKS(600));
    }
}

int main(void)
{
    // Create RTOS tasks
    xTaskCreate(sensors_read_task, "sensors_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(ecat_app_task, "ecat_task", 256, NULL, tskIDLE_PRIORITY + 1, NULL);

    vTaskStartScheduler();

    // Should never get here
    while (1)
    {
    }

    return 0;
}
