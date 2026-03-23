#include "camera.h"

#include "math.h"

Camera::Camera(const Vector3D look_from, const Vector3D look_at,
               const Vector3D view_up, const float field_of_view,
               const float aspect_ratio, const float aperture,
               const float focus_distance)
    : look_from(look_from) {
  const auto theta = degrees_to_radians(field_of_view);

  const auto viewport_height = 2.0f * std::tan(theta / 2.0f);

  const auto viewport_width = aspect_ratio * viewport_height;

  w = (look_from - look_at).normalize();

  u = cross(view_up, w).normalize();

  v = cross(w, u);

  horizontal = focus_distance * viewport_width * u;

  vertical = focus_distance * viewport_height * v;

  lower_left_corner =
      look_from - (horizontal / 2) - (vertical / 2) - (focus_distance * w);

  lens_radius = aperture / 2;
}

Ray Camera::get_ray(const float s, const float t) const {
  auto radius = lens_radius * Vector3D::in_unit_disk();

  auto offset = u * radius.x() + v * radius.y();

  return Ray(look_from + offset, lower_left_corner + s * horizontal +
                                     t * vertical - look_from - offset);
}
