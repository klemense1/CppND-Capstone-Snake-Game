#include "random_generator.h"

std::random_device Rand_Int::_dev = std::random_device();
std::mt19937 Rand_Int::_engine = std::mt19937(Rand_Int::_dev());
