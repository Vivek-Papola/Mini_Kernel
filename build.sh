#!/bin/bash

# Build bootloader
nasm -f bin boot/boot.asm -o boot.bin

# Build kernel
gcc -ffreestanding -c kernel/src/kernel.c -o kernel.o
nasm -f elf kernel/src/gdt.asm -o gdt.o
# Add other compilation commands

# Link kernel
ld -T boot/linker.ld -o kernel.bin kernel.o gdt.o # Add other objects

# Create ISO
mkdir -p iso/boot/grub
cp boot.bin iso/boot/
cp kernel.bin iso/boot/
cp boot/grub.cfg iso/boot/grub/
grub-mkrescue -o microkernel.iso iso/

echo "Build complete! Run with: qemu-system-i386 -cdrom microkernel.iso"
