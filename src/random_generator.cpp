#include "random_generator.h"

std::random_device RandomGenerator::_dev = std::random_device();
std::mt19937 RandomGenerator::_engine = std::mt19937(RandomGenerator::_dev());
