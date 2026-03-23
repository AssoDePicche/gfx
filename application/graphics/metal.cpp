#include "metal.h"

#include "geometry.h"
#include "vector3d.h"

Metal::Metal(const Vector3D& albedo, const float fuzziness)
    : _albedo(albedo), _fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f) {}

bool Metal::scatter(const Ray& ray, const Collision& collision,
                    Vector3D& attenuation, Ray& scattered) const {
  auto reflected = reflect(ray.direction().normalize(), collision.normal());

  scattered = Ray(collision.position(),
                  reflected + _fuzziness * Vector3D::in_unit_sphere());

  attenuation = _albedo;

  return dot(scattered.direction(), collision.normal()) > 0.0f;
}
