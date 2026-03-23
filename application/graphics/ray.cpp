#include "ray.h"

Ray::Ray(const Vector3D& origin, const Vector3D& direction)
    : _origin(origin), _direction(direction) {}

Vector3D Ray::origin(void) const { return _origin; }

Vector3D Ray::direction(void) const { return _direction; }

Vector3D Ray::position(const float k) const { return _origin + _direction * k; }
