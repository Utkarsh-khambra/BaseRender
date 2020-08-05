cmake_minimum_required(VERSION 3.0)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
set(OpenGL_GL_PREFERENCE GLVND)
project(example)
find_package(PkgConfig REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_executable(example test1.cpp

               ../../src/Window.cpp ../../include/Window.hpp
               ../../src/Input.cpp ../../include/Input.hpp
               ../../src/Camera.cpp ../../include/Camera.hpp
               ../../src/CameraFPS.cpp ../../include/CameraFPS.hpp
               ../../src/Shader.cpp ../../include/Shader.hpp
               ../../src/Program.cpp ../../include/Program.hpp
               ../../src/Mesh.cpp ../../include/Mesh.hpp
               ../../src/Object.cpp ../../include/Object.hpp
               ../../src/LoadObj.cpp ../../include/Object.hpp
               ../../src/Scene.cpp ../../include/Scene.hpp)
             target_link_libraries(example PRIVATE
        OpenGL::GL
        glfw
        ${GLEW_LIBRARIES} glm)
