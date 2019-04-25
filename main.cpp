#include "main.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// Create text representation of basic histogram
using iterator_t = std::vector<double>::const_iterator;
std::string dump_histogram(const iterator_t &begin, const iterator_t &end) {

  std::ostringstream out;
  if (std::distance(begin, end) > 0) {

    // Calculate max bin so we can scale the output
    const double max_bin{*std::max_element(begin, end)};

    // Max width of a bar
    const size_t max_bar_length = 70;

    std::for_each(begin, end, [&](const auto &bin) {
      out << std::string(1 + std::rint(max_bar_length * bin / max_bin), '_')
          << '\n';
    });
  }

  return out.str();
}

int main() {

  // Unit test me
  assert(dump_histogram(std::cbegin(input), std::cbegin(input)) == "" &&
         "Two copies of the same iterator should return empty string");
  assert(dump_histogram(std::cbegin(input), std::cend(input)) == output);

  // Read input one line at a time, dump histogram if we hit a blank line
  std::string line;
  std::vector<double> frame;
  while (std::getline(std::cin, line)) {

    if (line.empty()) {
      std::cout << dump_histogram(std::cbegin(frame), std::cend(frame)) << '\n';
      frame.clear();
    } else
      frame.push_back(std::stod(line));
  }

  if (frame.size())
    std::cout << dump_histogram(std::cbegin(frame), std::cend(frame)) << '\n';
}
