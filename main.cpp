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

  // Calculate max bin so we can scale the output
  const double max_bin{*std::max_element(begin, end)};

  // Max width of a bar
  const size_t max_bar_length = 70;

  std::ostringstream out;
  std::for_each(begin, end, [&](const auto &bin) {
    out << std::string(1 + std::rint(max_bar_length * bin / max_bin), '_')
        << '\n';
  });

  return out.str();
}

int main() {
  assert(dump_histogram(std::cbegin(input), std::cend(input)) == output);

  std::cout << "hello\n";

  while (std::cin.good())
    if (double val; std::cin >> val)
      std::cout << val << '\n';

  std::cout << "goodbye\n";
}
