
set(CMSIS_ROOT_PATH ${XMC_LIB_ROOT_PATH}/CMSIS)
set(FREERTOS_ROOT_PATH ${XMC_LIB_ROOT_PATH}/ThirdPartyLibraries/FreeRTOS/Source)
set(USB_LIB_ROOT_PATH ${CMAKE_SOURCE_DIR}/third-party/USB)
set(SOES_ROOT_PATH ${CMAKE_SOURCE_DIR}/third-party/soes)

###########################################################
######################## XMC LIBRARY ######################
add_library(xmc STATIC
    # XMC lib
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_gpio.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc4_gpio.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_i2c.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_uart.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_usic.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc4_scu.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_common.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc4_eru.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_eru.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_usbd.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_fce.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc4_flash.c
    ${XMC_LIB_ROOT_PATH}/XMCLib/src/xmc_ecat.c
    ${XMC_LIB_ROOT_PATH}/ThirdPartyLibraries/Newlib/syscalls.c
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

###########################################################
######################## USB LIBRARY ######################
add_library(usb STATIC
    ${USB_LIB_ROOT_PATH}/Class/
    ${USB_LIB_ROOT_PATH}/Class/Common/HIDParser.c
    ${USB_LIB_ROOT_PATH}/Class/Device/CDCClassDevice.c
    ${USB_LIB_ROOT_PATH}/Class/Device/HIDClassDevice.c
    ${USB_LIB_ROOT_PATH}/Class/Device/MassStorageClassDevice.c
    ${USB_LIB_ROOT_PATH}/Common/memcpy.c
    ${USB_LIB_ROOT_PATH}/Core/ConfigDescriptors.c
    ${USB_LIB_ROOT_PATH}/Core/Events.c
    ${USB_LIB_ROOT_PATH}/Core/HostStandardReq.c
    ${USB_LIB_ROOT_PATH}/Core/USBTask.c
    ${USB_LIB_ROOT_PATH}/Core/XMC4000/EndpointStream_XMC4000.c
    ${USB_LIB_ROOT_PATH}/Core/XMC4000/Endpoint_XMC4000.c
    ${USB_LIB_ROOT_PATH}/Core/XMC4000/USBController_XMC4000.c
)

target_include_directories(usb PUBLIC
    ${USB_LIB_ROOT_PATH}
    ${USB_LIB_ROOT_PATH}/Class
    ${USB_LIB_ROOT_PATH}/Class/Common
    ${USB_LIB_ROOT_PATH}/Class/Device
    ${USB_LIB_ROOT_PATH}/Common
    ${USB_LIB_ROOT_PATH}/Core
    ${USB_LIB_ROOT_PATH}/Core/XMC4000
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${CMSIS_ROOT_PATH}/Include
    ${CMSIS_ROOT_PATH}/Infineon/${DEVICE}_series/Include
)

target_compile_definitions(usb PRIVATE
    ${DEVICE}_${DEVICE_PACKAGE}x${DEVICE_MEM_SIZE}
)

###########################################################
########################## AS5600 #########################
add_library(as5600 STATIC
    ${CMAKE_SOURCE_DIR}/third-party/as5600/driver_as5600.c
)

target_include_directories(as5600 PUBLIC
    ${CMAKE_SOURCE_DIR}/third-party/as5600
)


###########################################################
########################### SOES ##########################
add_library(soes STATIC
    # soes
    ${SOES_ROOT_PATH}/ecat_slv.c
    ${SOES_ROOT_PATH}/esc_coe.c
    ${SOES_ROOT_PATH}/esc_eep.c
    ${SOES_ROOT_PATH}/esc_eoe.c
    ${SOES_ROOT_PATH}/esc_foe.c
    ${SOES_ROOT_PATH}/esc.c
    ${SOES_ROOT_PATH}/hal/xmc4/esc_hw_eep.c
    ${SOES_ROOT_PATH}/hal/xmc4/esc_hw.c
    ## app
    ${CMAKE_SOURCE_DIR}/src/ecat_app.c
    ${CMAKE_SOURCE_DIR}/src/objectlist.c
)

target_include_directories(soes PUBLIC
    ${SOES_ROOT_PATH}
    ${SOES_ROOT_PATH}/hal/xmc4
    ${SOES_ROOT_PATH}/include
    ${SOES_ROOT_PATH}/include/sys/gcc
    ${CMAKE_SOURCE_DIR}/inc
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${CMSIS_ROOT_PATH}/Include
    ${CMSIS_ROOT_PATH}/Infineon/${DEVICE}_series/Include
)

target_compile_options(soes PRIVATE
  -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
)

target_compile_definitions(soes PRIVATE
    ${DEVICE}_${DEVICE_PACKAGE}x${DEVICE_MEM_SIZE}
)

target_link_libraries(soes PUBLIC xmc)
