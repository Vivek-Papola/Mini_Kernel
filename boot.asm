[org 0x7c00]
[bits 16]

start:
    cli
    mov ax, 0
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    sti

    mov si, msg
    call print_string

    ; Load kernel
    mov bx, 0x1000
    mov dh, 15
    mov dl, [boot_drive]
    call disk_load

    ; Switch to protected mode
    call switch_to_pm

    jmp $

%include "gdt.asm"
%include "disk.asm"
%include "print.asm"
%include "pm_switch.asm"

[bits 32]
BEGIN_PM:
    call 0x1000  ; Jump to kernel
    jmp $

boot_drive db 0
msg db "Booting Microkernel OS...", 0

times 510-($-$$) db 0
dw 0xaa55
