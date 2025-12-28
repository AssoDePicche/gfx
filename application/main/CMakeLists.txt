if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
endif()

add_executable(${PROJECT_NAME} main.cpp)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE core platform glad::glad glfw OpenGL::GL)

install(TARGETS ${PROJECT_NAME} DESTINATION .)
