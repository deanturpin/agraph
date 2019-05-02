#include "draw.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <thread>

void plot(const double &v) {

  // Update display limits
  static double min{0}, max{0};
  min              = std::min(min, v);
  max              = std::max(max, v);
  const auto range = max - min;

  // On first call set smooth scrolling
  [[maybe_unused]] static const auto _init = [] {
    std::wcout << "\033[?4h";
    return 0u;
  }();

  // On first call get terminal width from environment or use default
  const static size_t max_bar_length = [] {
    if (const char *cols = std::getenv("COLUMNS"))
      return std::stoul(cols);
    else
      return 80ul;
  }();

  const size_t bar_length = std::rint(max_bar_length * (v - min) / range);

  // Print bar
  std::wcout << std::wstring(bar_length, '-') << '\n';

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(20ms);
}
