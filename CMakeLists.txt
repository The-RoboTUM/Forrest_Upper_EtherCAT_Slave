cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME upper_leg_ecat_slave)
project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(XMC_LIB_VERSION "2.1.16")
set(XMC_LIB_ROOT_PATH "${CMAKE_SOURCE_DIR}/third-party/XMC_Peripheral_Library_v${XMC_LIB_VERSION}/")

# Add executable
set(CMAKE_EXECUTABLE_SUFFIX ".elf")
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/encoder.cpp
    ${CMAKE_SOURCE_DIR}/src/logging/logging.cpp
    ${CMAKE_SOURCE_DIR}/src/logging/VirtualSerial.c
    ${CMAKE_SOURCE_DIR}/src/logging/Descriptors.c
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${XMC_LIB_ROOT_PATH}/XMCLib/inc
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/inc/logging
    ${CMAKE_SOURCE_DIR}/src
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

# soes lib already links xmc lib
target_link_libraries(${PROJECT_NAME} PRIVATE
    m
    c
    nosys
    usb
    as5600
    soes
)

# Link SII EEPROM binary into final image
set(SII_BIN_NAME sii_eeprom.bin)
set(SII_OBJ ${CMAKE_BINARY_DIR}/sii_eeprom_bin.o)

add_custom_command(
  OUTPUT ${SII_OBJ}
  COMMAND ${CMAKE_OBJCOPY} -I binary -O elf32-littlearm -B arm
          ${SII_BIN_NAME} ${SII_OBJ}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  DEPENDS ${CMAKE_SOURCE_DIR}/${SII_BIN_NAME}
  VERBATIM
)

add_custom_target(sii_blob ALL DEPENDS ${SII_OBJ})
add_dependencies(${PROJECT_NAME} sii_blob)

# Link the blob object into the final elf
target_link_libraries(${PROJECT_NAME} PRIVATE ${SII_OBJ})
