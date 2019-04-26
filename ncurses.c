#include <curses.h>
#include <unistd.h>

double _array[] = {1,2 , 3, 4};

size_t get_buffer(double * arr){
    usleep(100000);

    for (size_t i = 0; i < 4; ++i)
      arr[i] = _array[i];

  return 4;
}

int main() {

  // Init and hide the cursor
  initscr();
  curs_set(0);
    double buffer[1024];

  // Frame loop
  for (size_t i = 0; i < 20; ++i) {

    // Clear buffer
    erase();

    // Get values for this frame
    size_t n = get_buffer(buffer);

    // Draw
    for (size_t i = 0; i < n; ++i)
      mvaddstr(i+ 1, buffer[i], ".");

    // Render
    refresh();
  }

  // Tidy up
  endwin();
}
