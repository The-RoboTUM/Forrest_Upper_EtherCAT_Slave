# cmake/arm-gcc-toolchain.cmake

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(XMC_LIB_ROOT_PATH "/opt/XMCLib/XMC_Peripheral_Library_v2.1.16")

# Compiler flags
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")
set(CMAKE_C_FLAGS_INIT   "${MCU_FLAGS} -ffreestanding -fdata-sections -ffunction-sections")
set(CMAKE_CXX_FLAGS_INIT "${MCU_FLAGS} -ffreestanding -fno-exceptions -fno-rtti -fdata-sections -ffunction-sections")
set(CMAKE_ASM_FLAGS_INIT "${MCU_FLAGS}")

# Linker script
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/toolchain/XMC4500x1024.ld")

# Linker flags
set(CMAKE_EXE_LINKER_FLAGS_INIT
    "${MCU_FLAGS} -T${LINKER_SCRIPT} \
    -Wl,--gc-sections \
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map \
    -specs=nano.specs -specs=nosys.specs"
)

# XMC lib
set(CMAKE_FIND_ROOT_PATH ${XMC_LIB_ROOT_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
