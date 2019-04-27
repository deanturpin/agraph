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

using iterator_t = std::vector<double>::const_iterator;

// Scale bins
std::vector<double> scale_histogram(const iterator_t &begin,
                                    const iterator_t &end) {

  std::vector<double> scaled;

  std::for_each(begin, end, [&, n = 0](const auto &s) mutable {
    size_t index =
        std::rint(_default_raster.size() * n / std::distance(begin, end));

    // If it's a new bin create it
    if (index >= scaled.size())
      scaled.emplace_back();

    // Sum all the values that match a bin
    scaled.back() += s;

    ++n;
  });

  return scaled;
}

int unit_test() {

  const std::vector<double> t1(90);
  assert(scale_histogram(std::cbegin(t1), std::cend(t1)).size() ==
             _default_raster.size() &&
         "Scale function returns container of screen buffer width");

  return 0;
}

// Create text representation of basic histogram
void draw_histogram(const iterator_t &_begin, const iterator_t &_end) {

  // Run unit test on first invocation
  [[maybe_unused]] const static auto unit = unit_test();

  // Make a copy of default screen buffer
  auto screen_buffer = _default_screen_buffer;

  const auto scaled = scale_histogram(_begin, _end);

  const auto begin = std::cbegin(scaled);
  const auto end   = std::cend(scaled);

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
            h == bar_length - 1 ? '|' : '|';
    }
  }

  std::cout << screen_buffer_to_string(screen_buffer)
            << std::distance(_begin, _end) << '\n';
}

/* -------------------------------------- draw module ------ */

int main(int argc, char **argv) {

  unit_test();

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
