#!/usr/bin/env bash
set -e

mkdir -p Output

INC="-IDriver/GPIO/inc -IDriver/RCC/inc"
COMMON="-mcpu=cortex-m3 -mthumb -ffreestanding -fno-builtin -fdata-sections -ffunction-sections -Wall -Wextra -O0"

if command -v arm-none-eabi-gcc >/dev/null 2>&1; then
    CC=arm-none-eabi-gcc
    OBJCOPY=arm-none-eabi-objcopy

    "$CC" $COMMON $INC -c Driver/GPIO/src/GPIO.c -o Output/GPIO.o
    "$CC" $COMMON $INC -c Driver/RCC/src/RCC.c -o Output/RCC.o
    "$CC" $COMMON $INC -c Startup/startup.c -o Output/startup.o
    "$CC" $COMMON $INC -c main.c -o Output/main.o

    "$CC" -mcpu=cortex-m3 -mthumb -nostdlib \
        -Wl,-T,Linker/linker.ld -Wl,-Map=Output/main.map -Wl,--gc-sections \
        Output/startup.o Output/GPIO.o Output/RCC.o Output/main.o \
        -o Output/main.elf

    "$OBJCOPY" -O binary Output/main.elf Output/main.bin
elif command -v clang >/dev/null 2>&1 && command -v llvm-objcopy >/dev/null 2>&1; then
    CC="clang --target=arm-none-eabi"

    $CC $COMMON $INC -c Driver/GPIO/src/GPIO.c -o Output/GPIO.o
    $CC $COMMON $INC -c Driver/RCC/src/RCC.c -o Output/RCC.o
    $CC $COMMON $INC -c Startup/startup.c -o Output/startup.o
    $CC $COMMON $INC -c main.c -o Output/main.o

    $CC -mcpu=cortex-m3 -mthumb -nostdlib -fuse-ld=lld \
        -Wl,-T,Linker/linker.ld -Wl,-Map=Output/main.map -Wl,--gc-sections \
        Output/startup.o Output/GPIO.o Output/RCC.o Output/main.o \
        -o Output/main.elf

    llvm-objcopy -O binary Output/main.elf Output/main.bin
else
    echo "Khong tim thay arm-none-eabi-gcc hoac clang + llvm-objcopy."
    echo "Ubuntu/Debian: sudo apt update && sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi"
    exit 1
fi

echo "Build thanh cong. Cac file dau ra nam trong Output/."
