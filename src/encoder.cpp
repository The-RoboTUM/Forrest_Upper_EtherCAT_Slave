#include "encoder.h"
#include "hw_cfg.h"
#include "logging.h"
#include "driver_as5600.h"
#include "FreeRTOS.h"
#include "projdefs.h"
#include "task.h"
#include "xmc_i2c.h"
#include "xmc_usic.h"
#include "xmc_scu.h"

// ****************************************************** //
// *********************** DEFINES ********************** //
#define LOG_TAG "Encoder"
#define EMPTY_TX_BUFFER(I2C_CHANNEL)                                                \
    while (XMC_USIC_CH_GetTransmitBufferStatus(I2C_CHANNEL) & USIC_CH_TCSR_TDV_Msk) \
    {                                                                               \
    }
#define ENCODER_I2C_BAUDRATE 100000U

// ****************************************************** //
// ***************** PRIVATE FUNCTIONS ****************** //
uint8_t as5600_i2c_init(void)
{
    XMC_SCU_CLOCK_UngatePeripheralClock(XMC_SCU_PERIPHERAL_CLOCK_USIC1);

    XMC_I2C_CH_CONFIG_t i2c_cfg;
    i2c_cfg.baudrate = ENCODER_I2C_BAUDRATE;
    i2c_cfg.address = 0;

    XMC_I2C_CH_Init(USIC_CHANNEL_ENCODER, &i2c_cfg);
    XMC_I2C_CH_SetInputSource(USIC_CHANNEL_ENCODER,
                              XMC_I2C_CH_INPUT_SCL,
                              USIC1_C1_DX1_P0_13);
    XMC_I2C_CH_SetInputSource(XMC_I2C1_CH1,
                              XMC_I2C_CH_INPUT_SDA,
                              USIC1_C1_DX0_P3_15);
    XMC_USIC_CH_Enable(USIC_CHANNEL_ENCODER);
    XMC_I2C_CH_Start(USIC_CHANNEL_ENCODER);

    // Set up GPIO pins with I2C config
    struct XMC_GPIO_CONFIG i2c_scl;
    i2c_scl.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2;
    i2c_scl.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE;
    i2c_scl.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    XMC_GPIO_Init(PIN_ENCODER_I2C_SCL, &i2c_scl);

    struct XMC_GPIO_CONFIG i2c_sda;
    i2c_sda.mode = XMC_GPIO_MODE_OUTPUT_OPEN_DRAIN_ALT2;
    i2c_sda.output_strength = XMC_GPIO_OUTPUT_STRENGTH_STRONG_SOFT_EDGE;
    i2c_sda.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    XMC_GPIO_Init(P3_15, &i2c_sda);

    return 0;
};

uint8_t as5600_i2c_deinit(void)
{
    return 0;
};

void as5600_debug_print(const char *const fmt, ...)
{
    (void)fmt;
};

void as5600_delay_ms(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}

uint8_t as5600_i2c_read(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    XMC_I2C_CH_ClearStatusFlag(XMC_I2C1_CH1, 0xFFFFFFFFu);

    // Generate START condition and send address byte
    XMC_I2C_CH_MasterStart(USIC_CHANNEL_ENCODER, addr, XMC_I2C_CH_CMD_WRITE);
    EMPTY_TX_BUFFER(USIC_CHANNEL_ENCODER);

    XMC_I2C_CH_MasterTransmit(USIC_CHANNEL_ENCODER, reg);
    EMPTY_TX_BUFFER(USIC_CHANNEL_ENCODER);

    XMC_I2C_CH_MasterRepeatedStart(USIC_CHANNEL_ENCODER, addr, XMC_I2C_CH_CMD_READ);
    for (uint16_t i = 0; i < len; ++i)
    {
        if (i == (len - 1))
        {
            XMC_I2C_CH_MasterReceiveNack(USIC_CHANNEL_ENCODER);
        }
        else
        {
            XMC_I2C_CH_MasterReceiveAck(USIC_CHANNEL_ENCODER);
        }

        XMC_I2C_CH_ClearStatusFlag(USIC_CHANNEL_ENCODER, XMC_I2C_CH_STATUS_FLAG_RECEIVE_INDICATION);
        buf[i] = XMC_I2C_CH_GetReceivedData(USIC_CHANNEL_ENCODER);
    }

    XMC_I2C_CH_MasterStop(USIC_CHANNEL_ENCODER);
    return 0;
}

uint8_t as5600_i2c_write(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len)
{
    // Start transaction
    XMC_I2C_CH_MasterStart(USIC_CHANNEL_ENCODER, addr, XMC_I2C_CH_CMD_WRITE);
    while ((XMC_I2C_CH_GetStatusFlag(USIC_CHANNEL_ENCODER) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
        // wait for ACK
    }
    XMC_I2C_CH_ClearStatusFlag(USIC_CHANNEL_ENCODER, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    // Send register
    XMC_I2C_CH_MasterTransmit(USIC_CHANNEL_ENCODER, reg);
    while ((XMC_I2C_CH_GetStatusFlag(USIC_CHANNEL_ENCODER) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
    {
        // wait for ACK
    }
    XMC_I2C_CH_ClearStatusFlag(USIC_CHANNEL_ENCODER, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);

    // Transmit data from the buffer
    XMC_I2C_CH_MasterRepeatedStart(USIC_CHANNEL_ENCODER, addr, XMC_I2C_CH_CMD_WRITE);
    for (int i = 0; i < len; i++)
    {
        XMC_I2C_CH_MasterTransmit(USIC_CHANNEL_ENCODER, buf[i]);
        while ((XMC_I2C_CH_GetStatusFlag(USIC_CHANNEL_ENCODER) & XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED) == 0U)
        {
            // wait for ACK
        }
        XMC_I2C_CH_ClearStatusFlag(USIC_CHANNEL_ENCODER, XMC_I2C_CH_STATUS_FLAG_ACK_RECEIVED);
    }
    return 0;
}

// ****************************************************** //
// ******************* PUBLIC METHODS ******************* //
Encoder::Encoder(Encoder::Channel channel)
{
    (void)channel; // add multi-channel support

    DRIVER_AS5600_LINK_IIC_INIT(&this->sensor_handle, as5600_i2c_init);
    DRIVER_AS5600_LINK_IIC_DEINIT(&this->sensor_handle, as5600_i2c_deinit);
    DRIVER_AS5600_LINK_IIC_READ(&this->sensor_handle, as5600_i2c_read);
    DRIVER_AS5600_LINK_IIC_WRITE(&this->sensor_handle, as5600_i2c_write);
    DRIVER_AS5600_LINK_DELAY_MS(&this->sensor_handle, as5600_delay_ms);
    DRIVER_AS5600_LINK_DEBUG_PRINT(&this->sensor_handle, as5600_debug_print);

    int res = as5600_init(&this->sensor_handle);
    if (res != 0)
    {
        logger_println(LOG_TAG, "Error initializing as5600 %d", res);
    }
}

Encoder* Encoder::getInstance(enum Channel ch)
{
    static Encoder inst(Encoder::CHANNEL_0);
    return &inst;
}

uint32_t Encoder::read(void)
{
    return this->_cacheData;
}

int Encoder::fetch(void)
{
    uint8_t res;
    uint16_t angle_raw;
    float dummy;

    res = as5600_read(&this->sensor_handle, &angle_raw, &dummy);
    if (res != 0)
    {
        logger_println(LOG_TAG, "as5600 read failed.\n");
        return -1;
    }

    this->_cacheData = angle_raw * (360*ENCODER_SCALE) / (4096*ENCODER_SCALE);
    return res;
}
