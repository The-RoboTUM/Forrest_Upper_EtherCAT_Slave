cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME upper_leg_ecat_slave)
project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(XMC_LIB_ROOT_PATH "/opt/XMCLib/XMC_Peripheral_Library_v2.1.16/")

# Add executable
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
      src/main.cpp
      ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/XMC4800_series/Source/system_XMC4800.c
      ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/XMC4800_series/Source/GCC/startup_XMC4800.S
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${XMC_LIB_ROOT_PATH}/CMSIS/Include
    ${XMC_LIB_ROOT_PATH}/CMSIS/Infineon/XMC4800_series/Include
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    XMC4800_F100x1024
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
