#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> screen_buffer{
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
    "............................................................",
};

std::string screen_buffer_to_string() {

  std::ostringstream out;

  for (const auto &raster : screen_buffer)
    out << '|' << raster << '|' << '\n';

  return out.str();
}

// Create text representation of basic histogram
using iterator_t = std::vector<double>::const_iterator;
void draw_histogram(const iterator_t &begin, const iterator_t &end) {

  std::ostringstream out;
  if (std::distance(begin, end) > 0) {

    // Calculate max bin so we can scale the output
    const double max_bin{*std::max_element(begin, end)};

    // Max width of a bar
    const size_t max_bar_length = screen_buffer.size();

    std::for_each(begin, end, [&](const auto &bin) {
      out << std::string(1 + std::rint(max_bar_length * bin / max_bin), '_')
          << '\n';
    });
  }

  std::cout << screen_buffer_to_string() << '\n'; // out.str();
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
  uint64_t frames{};
  while (std::getline(in, line)) {

    std::istringstream ss(line);

    double v{};
    if (ss >> v)
      frame.push_back(v);

    else {
      draw_histogram(std::cbegin(frame), std::cend(frame));
      // std::cout << frames << " frames\n";
      // ++frames;
      frame.clear();
    }
  }

  if (frame.size()) // {
    draw_histogram(std::cbegin(frame), std::cend(frame));
  // std::cout << frames << " frames (end)\n";
  // }
}
