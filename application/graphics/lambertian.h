#pragma once

#include "material.h"

class Lambertian : public Material {
 public:
  Lambertian(const Vector3D&);

  virtual bool scatter(const Ray&, const Collision&, Vector3D&,
                       Ray&) const override;

  Vector3D albedo(void) const;

 private:
  Vector3D _albedo;
};
