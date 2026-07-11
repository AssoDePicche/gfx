add_library(core STATIC
  application.cpp
  clock.cpp
  window.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(stb REQUIRED)

target_link_libraries(core PRIVATE glad::glad glfw OpenGL::GL stb::stb)
