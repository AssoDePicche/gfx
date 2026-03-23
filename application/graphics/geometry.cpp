#include "graphics.h"

Vector3D Collision::position(void) const { return _position; }

Vector3D Collision::normal(void) const { return _normal; }

float Collision::t(void) const { return _t; }

std::shared_ptr<Material> Collision::material(void) const { return _material; }

bool Collision::front_face(void) const { return _front_face; }

void Collision::position(const Vector3D position) { _position = position; }

void Collision::normal(const Vector3D normal) { _normal = normal; }

void Collision::t(const float t) { _t = t; }

void Collision::material(std::shared_ptr<Material> material) {
  _material = material;
}

void Collision::front_face(const bool front_face) { _front_face = front_face; }

void Collision::set_face_normal(const Ray& ray,
                                const Vector3D& outward_normal) {
  front_face(dot(ray.direction(), outward_normal) < 0);

  _normal = _front_face ? outward_normal : -outward_normal;
}

Scene::Scene(const std::shared_ptr<Geometry> geometry) { add(geometry); }

void Scene::clear(void) { geometries.clear(); }

void Scene::add(const std::shared_ptr<Geometry> geometry) {
  geometries.push_back(geometry);
}

bool Scene::collide(const Ray& ray, const float t_min, const float t_max,
                    Collision& collision) const {
  Collision current_collision;

  bool collide_anything = false;

  auto closest_so_far = t_max;

  for (const auto& geometry : geometries) {
    if (!geometry->collide(ray, t_min, closest_so_far, current_collision)) {
      continue;
    }

    collide_anything = true;

    closest_so_far = current_collision.t();

    collision = current_collision;
  }

  return collide_anything;
}
