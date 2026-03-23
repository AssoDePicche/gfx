#pragma once

#include <cstdint>
#include <ostream>

class Vector3D final {
 public:
  Vector3D(void) = default;

  Vector3D(const float, const float, const float);

  float x(void) const;

  float y(void) const;

  float z(void) const;

  float length(void) const;

  Vector3D normalize(void) const;

  bool is_nearly_zero(void) const;

  Vector3D operator-(void) const;

  Vector3D& operator+=(const Vector3D&);

  Vector3D& operator*=(const float);

  Vector3D& operator/=(const float);

  static Vector3D random(void);

  static Vector3D random(const float, const float);

  static Vector3D in_unit_sphere(void);

  static Vector3D unit_vector(void);

  static Vector3D in_unit_disk(void);

  static Vector3D in_hemisphere(const Vector3D&);

 private:
  float _x = 0.0f, _y = 0.0f, _z = 0.0f;
};

std::ostream& operator<<(std::ostream&, const Vector3D&);

Vector3D operator+(const Vector3D&, const Vector3D&);

Vector3D operator-(const Vector3D&, const Vector3D&);

Vector3D operator*(const Vector3D&, const Vector3D&);

Vector3D operator*(const float, const Vector3D&);

Vector3D operator*(const Vector3D&, const float);

Vector3D operator/(const Vector3D&, const float);

float dot(const Vector3D&, const Vector3D&);

Vector3D cross(const Vector3D&, const Vector3D&);

Vector3D reflect(const Vector3D&, const Vector3D&);

Vector3D refract(const Vector3D&, const Vector3D&, const float);
