#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

const std::vector<double> input{
    15147, 2017,  26749, 3862,  2529,  19151, 28393, 13840, 1589,  785,   22937,
    20649, 13643, 30358, 7337,  12124, 19168, 29311, 4191,  24413, 30185, 13786,
    5016,  3991,  16232, 24969, 6851,  13793, 29429, 13119, 31250, 29336, 6312,
    26219, 8665,  20804, 24777, 23842, 5087,  8119,  10590,
};

// Create text representation of basic histogram
using iterator_t = std::vector<double>::const_iterator;
std::string dump_histogram(const iterator_t &begin, const iterator_t &end) {

  // Calculate max bin so we can scale the output
  const double max_bin{*std::max_element(begin, end)};

  // Max width of a bar
  const size_t max_bar_length = 70;

  std::ostringstream out;
  std::for_each(begin, end, [&](const auto &bin) {
    out << std::string(1 + std::rint(max_bar_length * bin / max_bin), '_') << '\n';
  });

  return out.str();
}

int main() {
const std::string status{std::to_string(input.size())};
  std::cout << dump_histogram(std::cbegin(input), std::cend(input)) << '\n'
             << status << '\n';
}
