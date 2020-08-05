/*
  Date -17/03/2019
  Object
*/
#pragma once
#include "Mesh.hpp"
#include <GL/glew.h>
#include <glm/glm.hpp>
class Mesh;
class Program;
class Object {
public:
  friend class Scene;
  Object();
  ~Object();
  void fill(glm::vec3 vertex);
  void fill(GLuint index);
  GLuint size();
  void translate(glm::vec3 distance);
  void rotate(GLfloat theta, glm::vec3 axis);
  void scale(glm::vec3 ratio);
  void setup(GLuint vao, GLenum dataUploadType, Program &programToUse);
  // GLuint data ();
  void render();

private:
  Mesh mesh_;
  GLint instances;
  glm::mat4 transform = glm::mat4(1.0f);
  Object *next = NULL;
  Program *programInUse;
};
