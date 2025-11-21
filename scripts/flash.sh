#!/bin/bash

# Select target device
DEVICE=""
if [[ "$1" == "xmc4500" ]]; then
    DEVICE="xmc4500"
else
    DEVICE="xmc4800"
fi
DEVICE_UPPERCASE=$(printf '%s' "$DEVICE" | tr '[:lower:]' '[:upper:]')
MEMORY_SIZE=1024

# Generate JLink commands file
cat > build/JLinkCommands <<EOF
h
loadfile build/upper_leg_ecat_slave.elf
r
g
q
EOF

# Flash
JLinkExe -Device $DEVICE_UPPERCASE-$MEMORY_SIZE -If SWD -Speed 1000 -CommanderScript build/JLinkCommands
