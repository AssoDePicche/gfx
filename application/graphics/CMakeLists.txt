add_library(graphics STATIC
  aabb.cpp
  camera.cpp
  cartesian.cpp
  color.cpp
  dielectric.cpp
  geometry.cpp
  lambertian.cpp
  math.cpp
  metal.cpp
  quadtree.cpp
  ray.cpp
  sphere.cpp
  vector3d.cpp
)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
