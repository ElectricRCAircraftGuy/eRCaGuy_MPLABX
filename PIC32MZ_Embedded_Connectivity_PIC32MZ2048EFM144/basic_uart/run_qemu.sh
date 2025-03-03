#!/usr/bin/env bash

# set -x

# GS
# Feb. 2025
# 
# See: 
# 1. https://github.com/ElectricRCAircraftGuy/vak-opensource/blob/master/microcontrollers/pic32-max32/qemu.sh
# 1. Read the readme here: 
#    https://github.com/ElectricRCAircraftGuy/vak-opensource/tree/master/microcontrollers/pic32-max32
# 1. https://github.com/sergev/qemu/issues/20#issuecomment-2641610865
# 1. https://github.com/chipKIT32/chipKIT-digiboot/blob/master/BootloadersCurrent-hex/chipKIT-Max32.hex


# if [ ! -e "binaries/chipKIT-Max32_bootloader.hex" ]; then
#     mkdir -p binaries
#     wget \
#         https://raw.githubusercontent.com/chipKIT32/chipKIT-digiboot/refs/heads/master/BootloadersCurrent-hex/chipKIT-Max32.hex \
#         -O binaries/chipKIT-Max32_bootloader.hex
# fi

echo "Running QEMU. Kill it from another terminal with 'pkill -f qemu-pic32'..."
qemu-pic32 -machine pic32mz-explorer16 \
    -nographic \
    -monitor none \
    -serial stdio \
    -kernel "basic_uart.X/dist/default/production/basic_uart.X.production.hex"
    # -bios "binaries/chipKIT-Max32_bootloader.hex" \

    # -d instr \
    # -D output.trace
