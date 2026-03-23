#include "lambertian.h"

#include "geometry.h"

Lambertian::Lambertian(const Vector3D& albedo) : _albedo(albedo) {}

bool Lambertian::scatter(const Ray& ray, const Collision& collision,
                         Vector3D& attenuation, Ray& scattered) const {
  auto direction = collision.normal() + Vector3D::unit_vector();

  if (direction.is_nearly_zero()) {
    direction = collision.normal();
  }

  scattered = Ray(collision.position(), direction);

  attenuation = _albedo;

  return true;
}
