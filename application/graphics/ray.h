#pragma once

#include "vector3d.h"

class Ray {
 public:
  Ray(void) = default;

  Ray(const Vector3D&, const Vector3D&);

  Vector3D origin(void) const;

  Vector3D direction(void) const;

  Vector3D position(const float) const;

 private:
  Vector3D _origin, _direction;
};
