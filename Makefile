all:
    @echo "Building Microkernel OS..."
    ./scripts/build.sh

run:
    qemu-system-i386 -cdrom microkernel.iso

clean:
    rm -f *.bin *.o *.iso
    rm -rf iso/
