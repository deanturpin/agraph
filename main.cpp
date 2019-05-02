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

  // Create container for incoming values
  // std::vector<double> frame;

  // Read values until we have a full frame
  // const size_t max_frame{1024};

  std::string line;
  while (std::getline(in, line)) {

    std::stringstream ss;
    ss.precision(10);
    ss << line;

    double v{};
    if (ss >> v)
      plot(v);
    else
      std::cout << "skip\n";

    // if (in >> v) {
    //   std::cout << "store " << v << "\n";

    //   // Store value
    //   frame.push_back(v);

    //   // Draw frame if we've exceeded frame size
    //   if (frame.size() >= max_frame) {
    //     draw_histogram(std::cbegin(frame), std::cend(frame));
    //     frame.clear();
    //   }
    // }
    // else
    //   std::cout << "skipping\n";
  }

  // std::cout << frame.size() << " samples\n";

  // If there's anything left then draw it
  // if (!frame.empty())
  //   draw_histogram(std::cbegin(frame), std::cend(frame));
}
