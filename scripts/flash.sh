#!/bin/bash

# Select target device
DEVICE="xmc4800"
DEVICE_UPPERCASE=$(printf '%s' "$DEVICE" | tr '[:lower:]' '[:upper:]')
DEVICE_MEM_SIZE=2048

# Generate JLink commands file
cat > build/JLinkCommands <<EOF
h
loadfile build/upper_leg_ecat_slave.elf
r
g
q
EOF

# Flash
JLinkExe -Device $DEVICE_UPPERCASE-$DEVICE_MEM_SIZE -If SWD -Speed 1000 -CommanderScript build/JLinkCommands
