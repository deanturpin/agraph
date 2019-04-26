#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// Initialise screen buffer
const std::string _default_raster(87, ' ');
const std::vector<std::string> _default_screen_buffer(43, _default_raster);

// Convert screen buffer into something that can be printed
std::string screen_buffer_to_string(std::vector<std::string> &buffer) {

  std::ostringstream out;
  for (const auto &raster : buffer)
    out << raster << '\n';

  return out.str();
}

// Create text representation of basic histogram
using iterator_t = std::vector<double>::const_iterator;
void draw_histogram(const iterator_t &begin, const iterator_t &end) {

  // Make a copy of default screen buffer
  auto screen_buffer = _default_screen_buffer;

  if (std::distance(begin, end) > 0) {

    // Calculate the largest bin so we can scale the output
    const double max_bin{*std::max_element(begin, end)};

    // Max width of a bar
    const size_t max_bar_length = screen_buffer.size();

    // Construct bar for each bin
    for (auto i = begin; i < end; ++i) {

      // Calculate the length of this bar given the max in the sample
      const size_t bar_length = std::rint(max_bar_length * *i / max_bin);

      for (size_t h = 0; h < bar_length; ++h)
        screen_buffer[max_bar_length - 1 - h][std::distance(begin, i)] =
            h == bar_length - 1 ? '-' : '!';
    }
  }

  std::cout << screen_buffer_to_string(screen_buffer)
            << std::distance(begin, end) << '\n';
}

// void unit_test() {
//   const std::vector<double> t1{};
//   assert(draw_histogram(std::cbegin(t1), std::cend(t1)) == "" &&
//          "Histogram of empty container is empty string");
//
//   const std::vector<double> t2{1, 2, 3};
//   assert(draw_histogram(std::cbegin(t2), std::cend(t2)) ==
//              R"(________________________
// ________________________________________________
// _______________________________________________________________________
// )" && "Histogram of populated container is known string");
// }

/* -------------------------------------- draw module ------ */

int main(int argc, char **argv) {

  // unit_test();

  // Read file if there is one, otherwise use stdin
  std::ifstream file{argv[1]};
  auto &in = argc > 1 ? file : std::cin;

  // Read input one line at a time, dump histogram if we hit a blank line
  std::string line;
  std::vector<double> frame;
  while (std::getline(in, line)) {

    if (line.empty() || frame.size() >= _default_raster.size()) {
      draw_histogram(std::cbegin(frame), std::cend(frame));
      frame.clear();
    } else
      frame.push_back(std::stod(line));
  }

  if (frame.size())
    draw_histogram(std::cbegin(frame), std::cend(frame));
}
