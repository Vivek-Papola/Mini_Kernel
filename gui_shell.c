#include "ui.h"
#include "keyboard.h"

void gui_shell_main() {
    init_ui();
    render_ui();
    
    while(1) {
        char key = keyboard_get_char();
        if(key) {
            if(key == 27) { // ESC
                active_component = -1;
                render_ui();
            }
            else {
                handle_keypress(key);
            }
        }
        
        // Check for mouse input (simulated via keyboard for now)
        // In a real system, you'd read from mouse driver
        if(key == 'm') {
            // Simulate mouse click at position
            handle_click(35, 8);
        }
    }
}
