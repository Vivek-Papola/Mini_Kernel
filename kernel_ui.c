#include "kernel.h"
#include "ui.h"  // Add this

void kernel_main() {
    // Initialize systems
    gdt_init();
    idt_init();
    keyboard_init();
    vga_clear();
    
    // Start GUI shell instead of CLI
    gui_shell_main();  // Replace shell_init()
}
