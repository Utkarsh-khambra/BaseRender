#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/Mesh.hpp"
#include "../include/Shader.hpp"
#include "../include/Program.hpp"

Mesh::Mesh () {}
Mesh::~Mesh () {}

void Mesh::fill (glm::vec3 vertex)
{
    GLfloat* temp = glm::value_ptr(vertex);
    mesh.push_back(temp[0]);
    mesh.push_back(temp[1]);
    mesh.push_back(temp[2]);
}

void Mesh::fill (GLuint index_)
{
    index.push_back(index_);
}

GLint Mesh::elementArraySize ()
{
    return index.size();
}

void Mesh::fillBuffers (GLuint vao, GLenum dataUploadType)
{
    glBindVertexArray(vao);
    GLuint temp,ebo;
    glGenBuffers(1, &temp);
    glGenBuffers(1, &ebo);
    bo[0] = temp;
    bo[1] = ebo;
    glBindBuffer(GL_ARRAY_BUFFER,temp);
    glBufferData(GL_ARRAY_BUFFER, mesh.size()*sizeof(GLfloat), mesh.data(), dataUploadType);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size()*sizeof(GLuint), index.data(), dataUploadType);
    // for (auto i = mesh.begin(); i != mesh.end(); i+=3)
    //     std::cout << *i <<' ' << *(i+1) << ' ' << *(i+2) << '\n';
    // std::cout << ebo << '\n';
}

void Mesh::addProgram (Program& program)
{
    glBindBuffer(GL_ARRAY_BUFFER, bo[0]);
    int count = 0;
    Shader* vertexShader = program.attachedShaders[VERTEX];
    for (int i = 0; i < vertexShader->availableShaders; ++i){
        glEnableVertexAttribArray(vertexShader->attribLocation[i]);
        glVertexAttribPointer(vertexShader->attribLocation[i], 3, GL_FLOAT, GL_FALSE, 6*sizeof(GLfloat), (void*)(6*i*sizeof(GLfloat)));
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (GLuint)2);
    // for (int i = 0; i <MAX_SHARED; ++i){
    //     if (program.objectsSharingProgram[i] != NULL)
    //         program.objectsSharingProgram[i] = this;
    // }
}

GLuint Mesh::totalVert ()
{
    return mesh.size();
}
