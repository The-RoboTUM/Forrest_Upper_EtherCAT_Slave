set(CMSIS_ROOT_PATH ${XMC_LIB_ROOT_PATH}/CMSIS)
set(FREERTOS_ROOT_PATH ${XMC_LIB_ROOT_PATH}/ThirdPartyLibraries/FreeRTOS/Source)

add_library(xmc STATIC
    # XMC lib
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_gpio.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc4_gpio.c
    # CMSIS
    ${CMSIS_ROOT_PATH}/Infineon/${DEVICE}_series/Source/system_${DEVICE}.c
    ${CMSIS_ROOT_PATH}/Infineon/${DEVICE}_series/Source/GCC/startup_${DEVICE}.S
    # FreeRTOS
    ${FREERTOS_ROOT_PATH}/tasks.c
    ${FREERTOS_ROOT_PATH}/queue.c
    ${FREERTOS_ROOT_PATH}/timers.c
    ${FREERTOS_ROOT_PATH}/list.c
    ${FREERTOS_ROOT_PATH}/event_groups.c
    ${FREERTOS_ROOT_PATH}/croutine.c
    ${FREERTOS_ROOT_PATH}/portable/GCC/ARM_CM4F/port.c
    ${FREERTOS_ROOT_PATH}/portable/MemMang/heap_4.c
)

target_include_directories(xmc PUBLIC 
    # Project
    # XMC lib
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    # CMSIS
    ${CMSIS_ROOT_PATH}/Include
    ${CMSIS_ROOT_PATH}/Infineon/${DEVICE}_series/Include
    # FreeRTOS
    ${CMAKE_SOURCE_DIR}/inc # For FreeRTOSConfig.h
    ${FREERTOS_ROOT_PATH}/include
    ${FREERTOS_ROOT_PATH}/portable/GCC/ARM_CM4F
)

target_compile_definitions(xmc PRIVATE
    ${DEVICE}_${DEVICE_PACKAGE}x${DEVICE_MEM_SIZE}
)

