#include "draw.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char **argv) {

  // Read file if there is one, otherwise use stdin
  std::ifstream file{argv[1]};
  auto &in = argc > 1 ? file : std::cin;

  // Create container for incoming values
  double v{};
  std::vector<double> frame;

  // Read values until we have a full frame
  const size_t max_frame{1024};
  while (in >> v) {

    // Store value
    frame.push_back(v);

    // Draw frame if we've exceeded frame size
    if (frame.size() >= max_frame) {
      draw_histogram(std::cbegin(frame), std::cend(frame));
      frame.clear();
    }
  }

  // If there's anything left then draw it
  if (!frame.empty())
    draw_histogram(std::cbegin(frame), std::cend(frame));
}
