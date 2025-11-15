#!/bin/bash

cmake -S . -B build \
  -DCMAKE_TOOLCHAIN_FILE=toolchain/arm-xmc4800-toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build
