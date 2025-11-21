#!/bin/bash

DEVICE=""
if [[ "$1" == "xmc4500" ]]; then
    DEVICE="xmc4500"
else
    DEVICE="xmc4800"
fi
DEVICE_UPPERCASE=$(printf '%s' "$DEVICE" | tr '[:lower:]' '[:upper:]')
DEVICE_MEM_SIZE=1024
DEVICE_PACKAGE="F100"

echo "Building debug target for $DEVICE..."

cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=toolchain/arm-$DEVICE-toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Debug \
  -DDEVICE=$DEVICE_UPPERCASE \
  -DDEVICE_MEM_SIZE=$DEVICE_MEM_SIZE \
  -DDEVICE_PACKAGE=$DEVICE_PACKAGE

cmake --build build
