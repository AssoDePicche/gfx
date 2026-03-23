#pragma once

#include <cstdint>

#include "cartesian.h"

struct AABB {
  Cartesian topLeft;
  uint32_t height;
  uint32_t width;

  AABB(const Cartesian &, const uint32_t, const uint32_t);

  [[nodiscard]] uint32_t MinX() const;

  [[nodiscard]] uint32_t MinY() const;

  [[nodiscard]] uint32_t MaxX() const;

  [[nodiscard]] uint32_t MaxY() const;

  [[nodiscard]] bool IsCartesianInside(const Cartesian &) const;

  [[nodiscard]] bool Intersect(const AABB &) const;
};

