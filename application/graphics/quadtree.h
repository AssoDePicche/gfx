#pragma once

#include <cstdint>
#include <vector>

#include "aabb.h"
#include "cartesian.h"

struct Quadtree {
 public:
  Quadtree* topLeft;
  Quadtree* topRight;
  Quadtree* bottomLeft;
  Quadtree* bottomRight;
  std::vector<Cartesian> cartesians;
  AABB aabb;
  uint32_t capacity;
  bool subdivided{false};

  Quadtree(const AABB&, const uint32_t);

  ~Quadtree();

  [[nodiscard]] bool Insert(const Cartesian&);

  void Subdivide();

  std::vector<Cartesian> Query(const AABB&);

 private:
  std::vector<Cartesian> Query(const AABB&, std::vector<Cartesian>&);
};
