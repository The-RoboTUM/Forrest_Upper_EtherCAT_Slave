#!/bin/bash

# Select target device
DEVICE="xmc4800"
DEVICE_UPPERCASE=$(printf '%s' "$DEVICE" | tr '[:lower:]' '[:upper:]')
DEIVCE_MEM_SIZE=2048

echo "file build/upper_leg_ecat_slave.elf;target remote localhost:2331;monitor reset;load;break main;" | sed 's/;/\n/g' > build/GDBCommands

# Launch debug session
JLinkGDBServer -device $DEVICE_UPPERCASE-$DEVICE_MEM_SIZE -endian little -if SWD -speed 1000 -halt -logtofile -log JLinkLog -silent -vd &
sleep 1
sh -ci "arm-none-eabi-gdb -command=build/GDBCommands -tui"
killall JLinkGDBServer
