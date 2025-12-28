cmake_minimum_required(VERSION 3.15)

project(Gfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(core)
add_subdirectory(platform)
add_subdirectory(main)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
