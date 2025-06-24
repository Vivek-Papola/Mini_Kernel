#include "kernel.h"
#include "vga.h"
#include "fs.h"
#include "shell.h"

void kernel_main() {
    vga_clear();
    vga_print("Microkernel OS v1.0\n");
    
    fs_init();
    shell_init();
    
    while(1) {
        shell_prompt();
    }
}
