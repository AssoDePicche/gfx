#pragma once

#include "material.h"

class Metal : public Material {
 public:
  Metal(const Vector3D&, const float);

  virtual bool scatter(const Ray&, const Collision&, Vector3D&,
                       Ray&) const override;

 private:
  Vector3D _albedo;
  float _fuzziness;
};
