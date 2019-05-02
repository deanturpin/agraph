#include "draw.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char **argv) {

  // Read file if there is one, otherwise use stdin
  std::ifstream file{argv[1]};
  auto &in = argc > 1 ? file : std::cin;

  // Extract lines until end of file
  std::string line;
  while (std::getline(in, line)) {

    // Push line into a string stream
    std::stringstream ss;
    ss.precision(10);
    ss << line;

    // If we can extract a double then print it
    double v{};
    if (ss >> v)
      plot(v);
  }
}
