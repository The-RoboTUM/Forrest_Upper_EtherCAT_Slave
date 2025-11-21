# 🦿 Upper Leg Ethercat Sensor Slave Controler
Ethercat slave controller forwarding I2C sensor data.

## Setup
From a Unix environment, make sure to have the following tools and libraries installed on your computer:
- ARM GNU toolchain: You can download [here](https://developer.arm.com/downloads/-/gnu-rm)
- SEGGER Programming tools: Download the J-Link Software and Documentation Pack [here](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPac)
- XMC library: install v2.1.16 of the XMC library into the `/opt` directory.

## Building the project
Run either the debug or release build script:
- `./scripts/build_debug.sh`
- `./scripts/build_release.sh`

## Flashing and debugging
You can flash using
- `./scripts/flash.sh`

And open a new GDB tui session with
- `./scripts/debug.sh`
alternatively, you can also use the Cortex-Debug extension on VS Code for easier debugging.
