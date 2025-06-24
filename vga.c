// Draw a rectangle
void vga_draw_rect(int x, int y, int width, int height, uint8_t color) {
    for(int row = y; row < y+height; row++) {
        for(int col = x; col < x+width; col++) {
            vga_putat(' ', col, row, color);
        }
    }
}

// Print centered text
void vga_print_centered(char* text, int row, uint8_t color) {
    int len = strlen(text);
    int col = (VGA_WIDTH - len) / 2;
    vga_print_at(col, row, color, text);
}

// Print at position
void vga_print_at(int x, int y, uint8_t color, char* text) {
    for(int i = 0; text[i]; i++) {
        vga_putat(text[i], x+i, y, color);
    }
}
