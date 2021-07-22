#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class Rand_Int {
public:
  Rand_Int(int low, int high) : dist{low, high} {}
  int operator()() { return dist(_engine); } // draw an int
private:
  static std::random_device _dev;
  static std::mt19937 _engine;
  std::uniform_int_distribution<> dist;
};

#endif