cmake_minimum_required(VERSION 3.0)
project(example)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
add_executable(example test.cpp ../../src/Window.cpp ../../include/Window.hpp)
find_package(glfw3 REQUIRED)

target_link_libraries(example
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}glfw
        ${GLEW_LIBRARIES})
