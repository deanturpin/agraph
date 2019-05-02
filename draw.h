#ifndef DRAW_H
#define DRAW_H
#include <vector>

using iterator_t = std::vector<double>::const_iterator;
void draw_histogram(const iterator_t &, const iterator_t &);
void plot(const double &);

#endif
