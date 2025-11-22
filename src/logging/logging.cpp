#include "logging.h"
#include "xmc_scu.h"
extern "C" {
#include "VirtualSerial.h"
}
#include "stdarg.h"

void logger_init(void) {
    // Setup settings for USB clock
    struct XMC_SCU_CLOCK_CONFIG cfg = {};
    cfg.syspll_config.n_div = 80;
    cfg.syspll_config.p_div = 2;
    cfg.syspll_config.k_div = 4;
    cfg.syspll_config.mode = XMC_SCU_CLOCK_SYSPLL_MODE_NORMAL;
    cfg.syspll_config.clksrc = XMC_SCU_CLOCK_SYSPLLCLKSRC_OSCHP;
    cfg.enable_oschp = true;
    cfg.calibration_mode = XMC_SCU_CLOCK_FOFI_CALIBRATION_MODE_FACTORY;
    cfg.fsys_clksrc = XMC_SCU_CLOCK_SYSCLKSRC_PLL;
    cfg.fsys_clkdiv = 1;
    cfg.fcpu_clkdiv = 1;
    cfg.fccu_clkdiv = 1;
    cfg.fperipheral_clkdiv = 1;
    XMC_SCU_CLOCK_Init(&cfg);

    XMC_SCU_CLOCK_EnableUsbPll();
    XMC_SCU_CLOCK_StartUsbPll(2, 64);
    XMC_SCU_CLOCK_SetUsbClockDivider(4);
    XMC_SCU_CLOCK_SetUsbClockSource(XMC_SCU_CLOCK_USBCLKSRC_USBPLL);
    XMC_SCU_CLOCK_EnableClock(XMC_SCU_CLOCK_USB);

    SystemCoreClockUpdate();

    USB_Init();
}

void logger_println(const char* TAG, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    printf("[%s]: ", TAG);
    vprintf(fmt, args);
    printf("\n\r");

    va_end(args);
}

// Retarget printf to use CDC
#if defined(__GNUC__)
extern "C" int _write(int fd, char *ptr, int len) {
    (void)fd;
    for (int i = 0; i < len; ++i) {
        CDC_Device_SendByte(&VirtualSerial_CDC_Interface, ptr[i]);
    }
    return len;
}
#else
#error "No support for other compilers"
#endif

