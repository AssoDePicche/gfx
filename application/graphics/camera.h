#pragma once

#include "ray.h"

class Camera {
 public:
  Camera(const Vector3D, const Vector3D, const Vector3D, const float,
         const float, const float, const float);

  Ray get_ray(const float, const float) const;

 private:
  Vector3D look_from, lower_left_corner, horizontal, vertical, u, v, w;
  float lens_radius;
};
