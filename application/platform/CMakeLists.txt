add_library(platform STATIC
  glfw.cpp
)

target_include_directories(platform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(stb REQUIRED)

target_link_libraries(platform PRIVATE core glad::glad glfw OpenGL::GL stb::stb)
