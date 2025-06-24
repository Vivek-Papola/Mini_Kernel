#ifndef UI_H
#define UI_H

#include "vga.h"

// UI Components
typedef struct {
    int x, y;
    int width, height;
    char* label;
    void (*action)();
} Button;

typedef struct {
    int x, y;
    char* label;
    char value[256];
    int cursor_pos;
    int max_length;
} TextField;

// UI Functions
void init_ui();
void render_ui();
void handle_click(int x, int y);
void draw_button(Button btn);
void draw_text_field(TextField field);
void draw_file_explorer();

// File Operations UI
void show_create_file_modal();
void show_delete_confirm(char* filename);
void show_rename_form(char* filename);

// Global UI State
extern Button file_buttons[10];
extern TextField filename_field;
extern int active_component;
extern int show_file_explorer;

#endif
