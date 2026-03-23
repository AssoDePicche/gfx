#pragma once

#include <cstdint>

#include "geometry.h"

struct Color {
  static const uint8_t MAX_COLOR_CHANNEL_VALUE = 255;

  float alpha;
  uint8_t red;
  uint8_t green;
  uint8_t blue;

  Color(const uint32_t, const uint32_t, const uint32_t, const float);
};

void write_color(std::ostream&, const Vector3D, const uint32_t);

Vector3D ray_color(const Ray&, const Geometry&, const uint32_t);
