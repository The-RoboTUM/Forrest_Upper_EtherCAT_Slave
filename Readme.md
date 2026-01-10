# 🦿 Upper Leg Ethercat Sensor Slave
Ethercat slave forwarding I2C sensor data.

## Setup
From a Unix environment, make sure to have the following tools and libraries installed on your computer:
- ARM GNU toolchain: You can download [here](https://developer.arm.com/downloads/-/gnu-rm)
- SEGGER Programming tools: Download the J-Link Software and Documentation Pack [here](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPac)

**If using Windows:**
It is possible to set up the environment using WSL with Ubuntu-24.04. In this case, make sure you install both the Arm toolchain and the Linux version of the SEGGER tools inside WSL.
Instructions to install WSL (Version 2) can be found on https://learn.microsoft.com/en-us/windows/wsl/install

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

### If using WSL
You may experience issues with the JLink commands on WSL due to it not finding the USB devices. If the window that pops up from the JLink tool asks directly for an IP connection, then WSL did not find the USB device. You can be sure if you don't see the JLink connection after running the following command inside WSL:
```bash
lsusb
```

To make WSL see the USB connection, use `usbipd` on Powershell to tell WSL about the port.
1. Inside a Powershell window, install usbipd
```Powershell
winget install usbipd
```

2. Plug in the debug port and list devices to find Bus ID. Inside Powershell:
```Powershell
usbipd list
```
You may get something like:
```
BUSID  VID:PID    DEVICE
2-3    1366:0105  SEGGER J-Link
```

3. Attach the Bus ID to WSL. Inside Powershell:
```Powershell
usbipd attach --wsl --busid 2-3
```

4. Back on WSL, verify you can now see the USB device:
```bash
lsusb
```
You must now see the device and should be ready to run the flash and debug scripts.