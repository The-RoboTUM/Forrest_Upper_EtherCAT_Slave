cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME upper_leg_ecat_slave)
project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(XMC_LIB_VERSION "2.1.16")
set(XMC_LIB_ROOT_PATH "${CMAKE_SOURCE_DIR}/third-party/XMC_Peripheral_Library_v${XMC_LIB_VERSION}/")

# For now, we only support XMC4500 or XM4800
if(NOT DEVICE MATCHES "^XMC4[58]00$")
    message(FATAL_ERROR "Target '${TARGET}' not supported.")
else()
    message("Building for target ${DEVICE}")
endif()

# Add executable
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/logging/logging.cpp
    ${CMAKE_SOURCE_DIR}/src/logging/VirtualSerial.c
    ${CMAKE_SOURCE_DIR}/src/logging/Descriptors.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/inc/logging
)

add_subdirectory(third-party)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    ${DEVICE}_${DEVICE_PACKAGE}x${DEVICE_MEM_SIZE}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    c
    nosys
    xmc
    usb
)
