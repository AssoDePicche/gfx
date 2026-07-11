#include "color.h"

#include <algorithm>
#include <cmath>

Color::Color(const uint32_t red, const uint32_t green, const uint32_t blue,
             float alpha) {
  this->red = red;
  this->green = green;
  this->blue = blue;
  this->alpha = alpha;
}

static uint32_t map_pixel_color(const float pixel, const float scale) {
  const auto MAX_INTENSITY = 256;

  const auto gamma_correction = std::sqrt(pixel * scale);

  return static_cast<uint32_t>(MAX_INTENSITY *
                               std::clamp(gamma_correction, 0.0f, 0.999f));
}

void write_color(std::ostream& out, const Vector3D pixel,
                 const uint32_t samples_per_pixel) {
  const auto scale = 1.0f / samples_per_pixel;

  auto r = map_pixel_color(pixel.x(), scale);

  auto g = map_pixel_color(pixel.y(), scale);

  auto b = map_pixel_color(pixel.z(), scale);

  out << r << ' ' << g << ' ' << b << '\n';
}

Vector3D ray_color(const Ray& ray, const Geometry& world,
                   const uint32_t depth) {
  if (depth == 0) {
    return Vector3D(0.0f, 0.0f, 0.0f);
  }

  Collision collision;

  if (world.collide(ray, 0.001f, INFINITY, collision)) {
    Ray scattered;

    Vector3D attenuation;

    if (collision.material()->scatter(ray, collision, attenuation, scattered)) {
      return attenuation * ray_color(scattered, world, depth - 1.0f);
    }

    return Vector3D(0.0f, 0.0f, 0.0f);
  }

  auto direction = ray.direction().normalize();

  auto t = 0.5f * (direction.y() + 1.0f);

  return (1.0f - t) * Vector3D(1.0f, 1.0f, 1.0f) +
         t * Vector3D(0.5f, 0.7f, 1.0f);
}
