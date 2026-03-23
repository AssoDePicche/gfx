#include "vector3d.h"

#include "math.h"

Vector3D::Vector3D(const float x, const float y, const float z)
    : _x(x), _y(y), _z(z) {}

float Vector3D::x(void) const { return _x; }

float Vector3D::y(void) const { return _y; }

float Vector3D::z(void) const { return _z; }

Vector3D Vector3D::operator-(void) const { return Vector3D(-x(), -y(), -z()); }

Vector3D& Vector3D::operator+=(const Vector3D& v) {
  _x += v.x();

  _y += v.y();

  _z += v.z();

  return *this;
}

Vector3D& Vector3D::operator*=(const float k) {
  _x *= k;

  _y *= k;

  _z *= k;

  return *this;
}

Vector3D& Vector3D::operator/=(const float k) { return *this *= (1 / k); }

float Vector3D::length(void) const { return sqrt(_x * _x + _y * _y + _z * _z); }

bool Vector3D::is_nearly_zero(void) const {
  const auto THRESHOLD = 1e-8;

  return fabs(x()) < THRESHOLD && fabs(y()) < THRESHOLD &&
         fabs(z()) < THRESHOLD;
}

Vector3D Vector3D::random(void) {
  return Vector3D(random_number(), random_number(), random_number());
}

Vector3D Vector3D::random(const float min, const float max) {
  return Vector3D(random_number(min, max), random_number(min, max),
                  random_number(min, max));
}

std::ostream& operator<<(std::ostream& stream, const Vector3D& u) {
  stream << u.x() << ' ' << u.y() << ' ' << u.z();

  return stream;
}

Vector3D operator+(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

Vector3D operator-(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

Vector3D operator*(const Vector3D& u, const Vector3D& v) {
  return Vector3D(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

Vector3D operator*(const Vector3D& u, const float k) {
  return Vector3D(k * u.x(), k * u.y(), k * u.z());
}

Vector3D operator*(const float k, const Vector3D& u) { return u * k; }

Vector3D operator/(const Vector3D& u, const float k) { return u * (1.0f / k); }

float dot(const Vector3D& u, const Vector3D& v) {
  return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

Vector3D cross(const Vector3D& u, const Vector3D& v) {
  const auto x = u.y() * v.z() - u.z() * v.y();

  const auto y = u.z() * v.x() - u.x() * v.z();

  const auto z = u.x() * v.y() - u.y() * v.x();

  return Vector3D(x, y, z);
}

Vector3D Vector3D::normalize(void) const { return (*this / length()); }

Vector3D Vector3D::in_unit_sphere(void) {
  while (true) {
    const auto u = Vector3D::random(-1.0f, 1.0f);

    if (pow(u.length(), 2.0f) < 1.0f) {
      return u;
    }
  }
}

Vector3D Vector3D::in_unit_disk(void) {
  while (true) {
    const auto u =
        Vector3D(random_number(-1.0f, 1.0f), random_number(-1.0f, 1.0f), 0.0f);

    if (pow(u.length(), 2.0f) < 1.0f) {
      return u;
    }
  }
}

Vector3D Vector3D::unit_vector(void) {
  return Vector3D::in_unit_sphere().normalize();
}

Vector3D Vector3D::in_hemisphere(const Vector3D& normal) {
  const auto u = Vector3D::in_unit_sphere();

  const auto same_direction = dot(u, normal) > 0.0f;

  if (same_direction) {
    return u;
  }

  return -u;
}

Vector3D reflect(const Vector3D& v, const Vector3D& normal) {
  return v - 2.0f * dot(v, normal) * normal;
}

Vector3D refract(const Vector3D& u, const Vector3D& normal, const float eta) {
  const auto cosine = fmin(dot(-u, normal), 1);

  const auto perpendicular = eta * (u + cosine * normal);

  const auto parallel =
      -sqrt(fabs(1.0f - pow(perpendicular.length(), 2.0f))) * normal;

  return perpendicular + parallel;
}
