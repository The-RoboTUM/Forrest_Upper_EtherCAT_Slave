#ifndef ENCODER_H
#define ENCODER_H

#include "driver_as5600.h"
#include "xmc_gpio.h"

class Encoder
{
private:
    XMC_GPIO_PORT_t* i2c_scl_port;
    int i2c_scl_pin;
    XMC_GPIO_PORT_t* i2c_sda_port;
    int i2c_sda_pin;

    as5600_handle_t sensor_handle;

public:
    enum class Channel {CHANNEL_0, CHANNEL_1, CHANNEL_COUNT};
    Encoder(Channel channel);

    int read(float* deg);
};

#endif // ENCODER_H
