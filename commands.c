#include "shell.h"
#include "fs.h"

void cmd_mkdir(char* args) {
    if(vfs_create(args, DIRECTORY) == 0) {
        vga_print("Directory created\n");
    } else {
        vga_print("Error creating directory\n");
    }
}

void cmd_rm(char* args) {
    if(vfs_delete(args) == 0) {
        vga_print("File removed\n");
    } else {
        vga_print("Error removing file\n");
    }
}

// Add other commands: touch, mv, ls, cat, etc.
