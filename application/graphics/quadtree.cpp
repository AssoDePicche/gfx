#include "quadtree.h"

Quadtree::~Quadtree() {
  delete topLeft;
  delete topRight;
  delete bottomLeft;
  delete bottomRight;
}

bool Quadtree::Insert(const Cartesian &cartesian) {
  if (!aabb.IsCartesianInside(cartesian)) {
    return false;
  }

  if (cartesians.size() < capacity) {
    cartesians.push_back(cartesian);

    return true;
  }

  if (!subdivided) {
    Subdivide();
  }

  if (topLeft->Insert(cartesian) || topRight->Insert(cartesian) || bottomLeft->Insert(cartesian) || bottomRight->Insert(cartesian)) {
    return true;
  }

  return false;
}

void Quadtree::Subdivide() {
  const uint32_t x = aabb.topLeft.x;

  const uint32_t y = aabb.topLeft.y;

  const uint32_t width = aabb.MaxX() / 2;

  const uint32_t height = aabb.MaxY() / 2;

  AABB topLeft(Cartesian(x, y), width, height);

  AABB topRight(Cartesian(x + width, y), width, height);

  AABB bottomLeft(Cartesian(x, y + height), width, height);

  AABB bottomRight(Cartesian(x + width, y + height), width, height);

  this->topLeft = new Quadtree(topLeft, capacity);

  this->topRight = new Quadtree(topRight, capacity);

  this->bottomLeft = new Quadtree(bottomLeft, capacity);

  this->bottomRight = new Quadtree(bottomRight, capacity);

  subdivided = true;
}

std::vector<Cartesian> Quadtree::Query(const AABB &aabb) {
    return Query(aabb, this->cartesians);
}

std::vector<Cartesian> Quadtree::Query(const AABB &aabb, std::vector<Cartesian> &cartesians) {
  if (!this->aabb.Intersect(aabb)) {
    return cartesians;
  }

  for (const auto &cartesian : this->cartesians) {
    cartesians.push_back(cartesian);
  }

  if (!this->subdivided) {
    return cartesians;
  }

  this->topLeft->Query(aabb, cartesians);

  this->topRight->Query(aabb, cartesians);

  this->bottomLeft->Query(aabb, cartesians);

  this->bottomRight->Query(aabb, cartesians);
}
