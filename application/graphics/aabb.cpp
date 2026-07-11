#include "aabb.h"

uint32_t AABB::MinX() const { return topLeft.x; }

uint32_t AABB::MinY() const { return topLeft.y; }

uint32_t AABB::MaxX() const { return topLeft.x + this->width; }

uint32_t AABB::MaxY() const { return topLeft.y + this->height; }

bool AABB::IsCartesianInside(const Cartesian& cartesian) const {
  const auto [x, y] = cartesian;

  return x >= MinX() && x <= MaxX() && y >= MinY() && y <= MaxY();
}

bool AABB::Intersect(const AABB& aabb) const {
  return MinX() <= aabb.MaxX() && MaxY() >= aabb.MinX() &&
         MinY() <= aabb.MaxY() && MaxY() >= aabb.MinY();
}
