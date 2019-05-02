#include "draw.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <iostream>
#include <sstream>
#include <string>

// Initialise screen buffer
const std::wstring _default_raster(87, ' ');
const std::vector<std::wstring> _default_screen_buffer(43, _default_raster);

// Convert screen buffer into something that can be printed
std::wstring screen_buffer_to_string(std::vector<std::wstring> &buffer) {

  std::wstringstream out;
  for (const auto &raster : buffer)
    out << raster << '\n';

  return out.str();
}

// Scale bins
// std::vector<double> scale_histogram(const iterator_t &begin,
//                                     const iterator_t &end) {
//
//   std::vector<double> scaled;
//
//   std::for_each(begin, end, [&, n = 0](const auto &s) mutable {
//     size_t index =
//         std::rint(_default_raster.size() * n / std::distance(begin, end));
//
//     // If it's a new bin create it
//     if (index >= scaled.size())
//       scaled.emplace_back();
//
//     // Sum all the values that match a bin
//     scaled.back() += s;
//
//     ++n;
//   });
//
//   return scaled;
// }

int unit_test() {

  const std::vector<double> t1(90);
  // assert(scale_histogram(std::cbegin(t1), std::cend(t1)).size() ==
  //            _default_raster.size() &&
  //        "Scale function returns container of screen buffer width");

  return 0;
}

// Create text representation of basic histogram
void draw_histogram(const iterator_t &_begin, const iterator_t &_end) {

  // Run unit test on first invocation
  [[maybe_unused]] const static auto unit = unit_test();

  // Make a copy of default screen buffer
  auto screen_buffer = _default_screen_buffer;

  // const auto scaled = scale_histogram(_begin, _end);

  const auto begin = _begin;
  const auto end   = _end;

  std::cout << std::distance(begin, end) << " samples\n";

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
        screen_buffer[max_bar_length - 1 - h][std::distance(begin, i)] = '|';
    }
  }

  std::wcout << screen_buffer_to_string(screen_buffer)
             << std::distance(_begin, _end) << '\n';
}

void plot(const double &v) {

  // Initialise screen buffer on first call
  auto screen_buffer = _default_screen_buffer;

  // static std::deque<double> plots;
  //
  // // Store recent plot
  // plots.push_back(v);
  //
  // // Drop the oldest plot if buffer is screen width
  // if (plots.size() > _default_raster.size())
  //   plots.pop_front();

  // Update display limits
  static double min{0}, max{0};
  min              = std::min(min, v);
  max              = std::max(max, v);
  const auto range = max - min;
  // ++min;
  // --max;

  // Esc[?4h	Set smooth scrolling

  // Max width of a bar
  size_t max_bar_length = 80;
  if (const char *cols = std::getenv("COLUMNS"))
    max_bar_length = std::stoul(cols);

  // 70; // screen_buffer.size();

  //
  // for (size_t i = 0; i < plots.size(); ++i) {
  //         const size_t bar_length = std::rint(max_bar_length * (plots.at(i) -
  //         min) / range);

  //   for (size_t h = 0; h < bar_length; ++h)
  //     screen_buffer[max_bar_length - 1 - h][_default_raster.size() - 1 - i] =
  //     '|';
  //   }
  //
  // std::cout
  // << min << ' '
  // << max << ' '
  // << range << '\n';

  const size_t bar_length = std::rint(max_bar_length * (v - min) / range);

  // Print bar one line up
  std::wcout << "\033[1A" << std::wstring(bar_length, '-') << '\n';

  // Print status one line down
  std::wcout << "\033[1B" << bar_length << '\n';

  // std::wcout << v << '\t' << std::wstring(bar_length, '-')
  //   << min << ' '
  //   << max << ' '
  //   << '\n';

  // std::wcout << screen_buffer_to_string(screen_buffer) << '\n';
}
