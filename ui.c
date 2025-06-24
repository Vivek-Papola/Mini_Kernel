#include "ui.h"
#include "string.h"
#include "fs.h"

// UI State
Button file_buttons[10];
TextField filename_field;
int active_component = -1;
int show_file_explorer = 1;

void init_ui() {
    // Initialize file explorer buttons
    for(int i = 0; i < 10; i++) {
        file_buttons[i] = (Button){5, 5 + i*3, 20, 2, "", NULL};
    }
    
    // Initialize filename field
    filename_field = (TextField){30, 5, "Filename:", "", 0, 32};
}

void render_ui() {
    vga_clear();
    
    // Draw title bar
    vga_draw_rect(0, 0, VGA_WIDTH, 1, 0x1F);
    vga_print_centered("Microkernel OS - File Manager", 0, 0x1F);
    
    // Draw menu bar
    vga_draw_rect(0, 1, VGA_WIDTH, 1, 0x70);
    vga_print_at(2, 1, 0x70, "[F1] New File");
    vga_print_at(18, 1, 0x70, "[F2] New Folder");
    vga_print_at(36, 1, 0x70, "[F3] Delete");
    vga_print_at(48, 1, 0x70, "[F4] Rename");
    vga_print_at(60, 1, 0x70, "[F5] Refresh");
    
    // Draw main content area
    vga_draw_rect(0, 2, VGA_WIDTH, VGA_HEIGHT-3, 0x0F);
    
    if(show_file_explorer) {
        draw_file_explorer();
    }
    
    // Draw status bar
    vga_draw_rect(0, VGA_HEIGHT-1, VGA_WIDTH, 1, 0x70);
    vga_print_at(2, VGA_HEIGHT-1, 0x70, "Ready");
}

void draw_file_explorer() {
    // Draw file explorer panel
    vga_draw_rect(2, 3, 26, VGA_HEIGHT-5, 0x1F);
    vga_print_centered("File Explorer", 3, 0x1F);
    
    // Draw files (simplified)
    vga_print_at(4, 5, 0x1F, "> documents");
    vga_print_at(4, 7, 0x1F, "> images");
    vga_print_at(4, 9, 0x1F, "> system");
    
    // Draw action panel
    vga_draw_rect(30, 3, VGA_WIDTH-32, VGA_HEIGHT-5, 0x1F);
    vga_print_centered("Actions", 3, 0x1F);
    
    // Draw buttons
    Button new_file = {35, 7, 20, 3, "Create File", show_create_file_modal};
    Button new_folder = {35, 11, 20, 3, "Create Folder", NULL};
    Button delete = {35, 15, 20, 3, "Delete", NULL};
    
    draw_button(new_file);
    draw_button(new_folder);
    draw_button(delete);
}

void draw_button(Button btn) {
    // Draw button with border
    vga_draw_rect(btn.x, btn.y, btn.width, btn.height, 0x70);
    vga_draw_rect(btn.x+1, btn.y+1, btn.width-2, btn.height-2, 0x07);
    
    // Center text in button
    int text_x = btn.x + (btn.width - strlen(btn.label)) / 2;
    int text_y = btn.y + btn.height / 2;
    vga_print_at(text_x, text_y, 0x07, btn.label);
}

void draw_text_field(TextField field) {
    // Draw label
    vga_print_at(field.x, field.y, 0x0F, field.label);
    
    // Draw text box
    vga_draw_rect(field.x, field.y+1, 30, 1, 0x70);
    vga_print_at(field.x+1, field.y+1, 0x0F, field.value);
    
    // Draw cursor if active
    if(active_component == 1) {
        vga_putat('_', field.x+1+field.cursor_pos, field.y+1, 0x0F);
    }
}

void show_create_file_modal() {
    // Draw modal overlay
    vga_draw_rect(20, 8, 40, 8, 0x47);
    vga_draw_rect(21, 9, 38, 6, 0x17);
    
    // Draw title
    vga_print_centered("Create New File", 9, 0x17);
    
    // Draw text field
    filename_field.x = 25;
    filename_field.y = 11;
    draw_text_field(filename_field);
    
    // Draw buttons
    Button ok = {30, 13, 8, 2, "OK", NULL};
    Button cancel = {42, 13, 8, 2, "Cancel", NULL};
    draw_button(ok);
    draw_button(cancel);
    
    active_component = 1;
}

void handle_click(int x, int y) {
    // Handle button clicks
    if(x >= 35 && x <= 55) {
        if(y >= 7 && y <= 10) {
            show_create_file_modal();
        }
        // Handle other buttons...
    }
    
    // Handle modal buttons
    if(active_component == 1) {
        if(y == 13) {
            if(x >= 30 && x <= 38) {
                // Create file
                vfs_create(filename_field.value, REGULAR);
                active_component = -1;
                render_ui();
            }
            else if(x >= 42 && x <= 50) {
                // Cancel
                active_component = -1;
                render_ui();
            }
        }
    }
}

void handle_keypress(char key) {
    if(active_component == 1) {
        // Handle text input
        if(key >= 32 && key <= 126) {
            if(strlen(filename_field.value) < filename_field.max_length) {
                // Insert character
                memmove(&filename_field.value[filename_field.cursor_pos+1], 
                        &filename_field.value[filename_field.cursor_pos],
                        strlen(filename_field.value) - filename_field.cursor_pos + 1);
                filename_field.value[filename_field.cursor_pos] = key;
                filename_field.cursor_pos++;
            }
        }
        else if(key == 8) { // Backspace
            if(filename_field.cursor_pos > 0) {
                memmove(&filename_field.value[filename_field.cursor_pos-1], 
                        &filename_field.value[filename_field.cursor_pos],
                        strlen(filename_field.value) - filename_field.cursor_pos + 1);
                filename_field.cursor_pos--;
            }
        }
        render_ui();
    }
}
