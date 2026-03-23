#pragma once

#include "ray.h"

class Collision;

class Material {
 public:
  virtual bool scatter(const Ray&, const Collision&, Vector3D&, Ray&) const = 0;
};
