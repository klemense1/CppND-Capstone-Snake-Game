#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

class RandomGenerator {
public:
//   RandomGenerator();
  static std::random_device _dev;
  static std::mt19937 _engine;
};

#endif