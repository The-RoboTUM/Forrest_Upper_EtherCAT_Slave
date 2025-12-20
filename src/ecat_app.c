#include "ecat_app.h"
#include "ecat_slv.h"
#include "hw_cfg.h"
#include "utypes.h"

extern void ESC_eep_handler(void);

_Objects Obj;
uint8_t * rxpdo = (uint8_t *)&Obj.LED;
uint8_t * txpdo = (uint8_t *)&Obj.Encoder1;

void cb_get_inputs (void)
{
}

void cb_set_outputs (void)
{
}

void ecat_app_task(void* pvParams)
{
    (void)pvParams;

   /* Setup config hooks */
   static esc_cfg_t config = {
      .user_arg = NULL,
      .use_interrupt = 0,
      .watchdog_cnt = 5000,
      .set_defaults_hook = NULL,
      .pre_state_change_hook = NULL,
      .post_state_change_hook = NULL,
      .application_hook = NULL,
      .safeoutput_override = NULL,
      .pre_object_download_hook = NULL,
      .post_object_download_hook = NULL,
      .rxpdo_override = NULL,
      .txpdo_override = NULL,
      .esc_hw_interrupt_enable = NULL,
      .esc_hw_interrupt_disable = NULL,
      .esc_hw_eep_handler = ESC_eep_handler
   };

   static const XMC_GPIO_CONFIG_t gpio_config_led = {
        .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
        .output_level = XMC_GPIO_OUTPUT_LEVEL_LOW,
        .output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE
    };

   // configure I/O
   XMC_GPIO_Init(PIN_LED, &gpio_config_led);

   ecat_slv_init (&config);

   while (1) {
      ecat_slv();
   }
}