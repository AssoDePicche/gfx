add_library(core STATIC
  application.cpp
  clock.cpp
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
