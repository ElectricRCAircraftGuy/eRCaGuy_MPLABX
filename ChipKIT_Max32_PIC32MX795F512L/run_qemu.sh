#!/usr/bin/env bash

set -x

# See: 
# 1. https://github.com/sergev/qemu/issues/20#issuecomment-2641610865
# 1. https://github.com/chipKIT32/chipKIT-digiboot/blob/master/BootloadersCurrent-hex/chipKIT-Max32.hex

if [ ! -e "binaries/chipKIT-Max32_bootloader.hex"]; then
    echo "suck"
fi

exit 1

qemu-pic32 -machine pic32mx7-max32 \
    -nographic \
    -monitor none \
    -serial stdio \
    -bios ../max32-demo/arduino-bootloader.X.Max32.hex \
    -kernel uart.hex

#    -d instr \
#    -D out.trace
