#pragma once
#include <string>
GLushort const MAX_SHADER_TYPES = 2;
GLushort const MAX_ATTRIBS = 2;
GLushort const MAX_UNIFORM_BLOCKS = 3;
enum _ShaderType : GLuint { VERTEX = 0, FRAGMENT, ALL };
struct Shader;
class Object;
#include "Mesh.hpp"
class Program {
public:
  Program();
  void bindShader(Shader &shader, GLuint whichShaderType);
  void makeProgram();
  GLuint id();
  void sharedUniform(std::string uniformBlockName, GLuint bindingIndex);
  GLuint
  makeSharedUniformBuffer(std::size_t bufferSize,
                          GLuint bindingIndex); // return buffer reference
  void bindUniformBuffer(GLuint bufferRef);
  void fillUniformBuffer(GLuint bufferRef, const GLfloat *data,
                         std::size_t dataSize, GLuint offset);
  void setUniform(std::string name, std::vector<GLfloat> values);
  void setUniformMatrix4(std::string name, glm::mat4 &mat);
  void setUniformMatrix3(std::string name, glm::mat3 *mat);
  void setUniformMatrix2(std::string name, glm::mat2 *mat);
  friend void Mesh::addProgram(Program &prog);

private:
  std::array<Shader *, MAX_SHADER_TYPES> attachedShaders;
  std::vector<GLuint> uniforms;
  GLuint uniformBlockIndex[MAX_UNIFORM_BLOCKS];
  GLuint programID;
  // std::map<std::string, GLuint> ubo;
};
