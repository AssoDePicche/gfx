#include "math.h"

#include <random>

float degrees_to_radians(const float degrees) {
  return degrees * std::numbers::pi / 180.0f;
}

float random_number(const float min, const float max) {
  static std::random_device device;

  static std::mt19937 mersenne_twister(device());

  static std::uniform_real_distribution<float> distribution(min, max);

  return distribution(mersenne_twister);
}
