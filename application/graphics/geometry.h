#pragma once

#include <memory>
#include <vector>

#include "material.h"
#include "ray.h"

class Collision {
 public:
  Collision(void) = default;

  Vector3D position(void) const;

  Vector3D normal(void) const;

  float t(void) const;

  std::shared_ptr<Material> material(void) const;

  bool front_face(void) const;

  void position(const Vector3D);

  void normal(const Vector3D);

  void t(const float);

  void material(std::shared_ptr<Material> material);

  void front_face(const bool);

  void set_face_normal(const Ray&, const Vector3D&);

 private:
  Vector3D _position;
  Vector3D _normal;
  std::shared_ptr<Material> _material;
  float _t;
  bool _front_face;
};

class Geometry {
 public:
  virtual bool collide(const Ray&, const float, const float,
                       Collision&) const = 0;
};

class Scene : public Geometry {
 public:
  Scene(void) = default;

  Scene(const std::shared_ptr<Geometry>);

  void clear(void);

  void add(const std::shared_ptr<Geometry>);

  virtual bool collide(const Ray&, const float, const float,
                       Collision&) const override;

 private:
  std::vector<std::shared_ptr<Geometry>> geometries;
};
