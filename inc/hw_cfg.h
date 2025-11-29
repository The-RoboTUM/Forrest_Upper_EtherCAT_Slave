#ifndef HW_CFG_H
#define HW_CFG_H

#include "xmc_gpio.h"
#include "xmc_usic.h"

#define PIN_ENCODER_I2C_SCL P0_13
#define PIN_ENCODER_I2C_SDA P3_15

#define USIC_CHANNEL_ENCODER XMC_I2C1_CH1

#define USIC_PIN_ENCODER_SCL USIC1_C1_DX1_P0_13
#define USIC_PIN_ENCODER_SDA USIC1_C1_DX0_P3_15

#endif // HW_CFG_H
