#pragma once

#include "material.h"

class Dielectric : public Material {
 public:
  Dielectric(const float);

  virtual bool scatter(const Ray&, const Collision&, Vector3D&,
                       Ray&) const override;

 private:
  float _index_of_refraction;

  static float reflectance(const float, const float);
};
