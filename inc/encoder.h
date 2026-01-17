#ifndef ENCODER_H
#define ENCODER_H

#include "driver_as5600.h"
#include "xmc_gpio.h"

#define ENCODER_SCALE 1000

class Encoder
{
public:
    enum Channel
    {
        CHANNEL_0,
        CHANNEL_1,
        CHANNEL_COUNT
    };

    static Encoder* getInstance(enum Channel ch);

    uint32_t read(void);
    int      fetch(void);

private:
    as5600_handle_t sensor_handle;
    uint32_t        _cacheData;

    Encoder(Channel channel);
};

#endif // ENCODER_H
