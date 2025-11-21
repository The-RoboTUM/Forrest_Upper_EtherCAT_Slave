cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME upper_leg_ecat_slave)
project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(XMC_LIB_ROOT_PATH "/opt/XMCLib/XMC_Peripheral_Library_v2.1.16/")

# For now, we only support XMC4500 or XM4800
if(NOT DEVICE MATCHES "^XMC4[58]00$")
    message(FATAL_ERROR "Target '${TARGET}' not supported.")
else()
    message("Building for target ${DEVICE}")
endif()

# Add executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/${DEVICE}_series/Source/system_${DEVICE}.c
    ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/${DEVICE}_series/Source/GCC/startup_${DEVICE}.S
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${XMC_LIB_ROOT_PATH}/CMSIS/Include
    ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/${DEVICE}_series/Include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${DEVICE}_F100x1024
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    c
    nosys
)
