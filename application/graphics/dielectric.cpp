#include "dielectric.h"

#include "geometry.h"
#include "math.h"
#include "ray.h"

Dielectric::Dielectric(const float index_of_refraction)
    : _index_of_refraction(index_of_refraction){};

bool Dielectric::scatter(const Ray& ray, const Collision& collision,
                         Vector3D& attenuation, Ray& scattered) const {
  attenuation = Vector3D(1.0f, 1.0f, 1.0f);

  const auto refraction = collision.front_face() ? (1.0f / _index_of_refraction)
                                                 : _index_of_refraction;

  auto direction = ray.direction().normalize();

  const auto cosine = std::fmin(dot(-direction, collision.normal()), 1.0f);

  const auto sine = std::sqrt(1.0f - std::pow(cosine, 2.0f));

  bool cannot_refract = (refraction * sine) > 1.0f;

  if (cannot_refract || reflectance(cosine, refraction) > random_number()) {
    direction = reflect(direction, collision.normal());
  } else {
    direction = refract(direction, collision.normal(), refraction);
  }

  scattered = Ray(collision.position(), direction);

  return true;
}

float Dielectric::reflectance(const float cosine, const float recraction) {
  const auto theta = std::pow((1.0f - recraction) / (1.0f + recraction), 2.0f);

  return theta + (1.0f - theta) * std::pow((1.0f - cosine), 5.0f);
}
