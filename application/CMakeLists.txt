cmake_minimum_required(VERSION 3.15)

project(Gfx LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

enable_testing()

add_subdirectory(core)
add_subdirectory(graphics)
add_subdirectory(platform)
add_subdirectory(main)
add_subdirectory(test)

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/bin)
