#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
class Program;
class Mesh {
public:
  Mesh();
  ~Mesh();
  void fill(glm::vec3 vertex);
  void fill(GLuint index_);
  GLint elementArraySize();
  GLuint totalVert();
  void fillBuffers(GLuint vao, GLenum dataUploadType);
  // GLuint* getBuffer ();
  void addProgram(Program &program);

private:
  std::vector<GLfloat> mesh; // formated in VVVNNN way
  std::vector<GLuint> index;
  GLuint bo[2];
  // GLuint buffers[2]; // [0] Data buffer & [1] Element Buffer
};
