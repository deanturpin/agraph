#include "draw.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int main(int argc, char **argv) {

  // Read file if there is one, otherwise use stdin
  std::ifstream file{argv[1]};
  auto &in = argc > 1 ? file : std::cin;

  // Read input one line at a time, dump histogram if we hit a blank line
  std::string line;
  std::vector<double> frame;
  while (std::getline(in, line)) {

    if (line.empty() || frame.size() >= 1024) {
      draw_histogram(std::cbegin(frame), std::cend(frame));
      frame.clear();
    } else
      frame.push_back(std::abs(std::stod(line)));
  }

  if (frame.size())
    draw_histogram(std::cbegin(frame), std::cend(frame));
}
