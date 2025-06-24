#include "shell.h"
#include "vga.h"

void shell_init() {
    vga_print("Type 'help' for available commands\n");
}

void shell_prompt() {
    vga_print("\nuser@microkernel:~$ ");
    char input[256];
    shell_read(input);
    shell_execute(input);
}

// Add command parsing and execution logic...
