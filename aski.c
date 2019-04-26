#include <curses.h>
#include <unistd.h>

int main() {

    // Init and hide the cursor
    curs_set(0);
    initscr();
    
    // Frame loop
    for (size_t i = 0; i < 10; ++i) {
        
        // Clear buffer
        erase();
        
        // Draw
        mvaddstr(i, i, ".");
        
        // Render
        refresh();
        usleep(100000);
    }
    
    // Tidy up
    endwin();
}