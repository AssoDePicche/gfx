#include "sphere.h"

#include <cmath>

Sphere::Sphere(const Vector3D center, const float radius,
               std::shared_ptr<Material> material)
    : _center(center), _radius(radius), _material(material) {}

bool Sphere::collide(const Ray& ray, const float t_min, const float t_max,
                     Collision& collision) const {
  Vector3D oc = ray.origin() - _center;

  auto a = std::pow(ray.direction().length(), 2.0f);

  auto half_b = dot(oc, ray.direction());

  auto c = std::pow(oc.length(), 2.0f) - std::pow(_radius, 2.0f);

  auto discriminant = half_b * half_b - a * c;

  if (discriminant < 0.0f) {
    return false;
  }

  auto square_root_of_discriminant = std::sqrt(discriminant);

  auto root = (-half_b - square_root_of_discriminant) / a;

  if (root < t_min || t_max < root) {
    root = (-half_b + square_root_of_discriminant) / a;

    if (root < t_min || t_max < root) {
      return false;
    }
  }

  collision.t(root);

  collision.position(ray.position(collision.t()));

  auto outward_normal = (collision.position() - _center) / _radius;

  collision.set_face_normal(ray, outward_normal);

  collision.material(_material);

  return true;
}
