#!/bin/bash

arm-none-eabi-gcc main.c startup.c vendor/CMSIS_5/Device/ST/cmsis-device-f4/Source/Templates/system_stm32f4xx.c \
    -T linker_script.ld -o blink.elf -Ivendor/CMSIS_5/CMSIS/Core/Include -Ivendor/CMSIS_5/Device/ST/cmsis-device-f4/Include \
    -mcpu=cortex-m4 -mthumb -nostdlib -DSTM32F411xE
