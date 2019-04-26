#include <curses.h>
#include <unistd.h>

int main() {

  // Init and hide the cursor
  initscr();
  curs_set(0);

  // Frame loop
  for (size_t i = 0; i < 100; ++i) {

    // Clear buffer
    // erase();

    // Draw
    mvaddstr(i, i*2, ".");

    // Render
    refresh();
    usleep(100000);
  }

  // Tidy up
  endwin();
}
