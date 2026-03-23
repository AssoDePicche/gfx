#pragma once

#include "geometry.h"

class Sphere : public Geometry {
 public:
  Sphere(void) = default;

  Sphere(const Vector3D, const float, std::shared_ptr<Material>);

  virtual bool collide(const Ray&, const float, const float,
                       Collision&) const override;

 private:
  Vector3D _center;
  float _radius;
  std::shared_ptr<Material> _material;
};
