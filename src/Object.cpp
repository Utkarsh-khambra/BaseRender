#include <vector>
#include <array>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../include/Mesh.hpp"
#include "../include/Object.hpp"
#include "../include/Program.hpp"

Object::Object () {}
Object::~Object () {}

void Object::fill (glm::vec3 vertex)
{
    mesh_.fill(vertex);
}

void Object::fill (GLuint index)
{
    mesh_.fill(index);
}

GLuint Object::size ()
{
    return mesh_.totalVert()/2;
}

void Object::translate (glm::vec3 distance)
{
    transform = glm::translate(transform, distance);
}

void Object::rotate (GLfloat theta, glm::vec3 axis)
{
    transform = glm::rotate(transform, theta, axis);
}

void Object::scale (glm::vec3 ratio)
{
    transform = glm::scale(transform, ratio);
}

void Object::setup (GLuint vao, GLenum dataUploadType, Program& programToUse)
{
    mesh_.fillBuffers(vao, dataUploadType);
    mesh_.addProgram(programToUse);
    programInUse = &programToUse;
}

// GLuint Object::data ()
// {
//     return mesh_.elementArraySize();
// }

void Object::render ()
{
    glUseProgram(programInUse->id());
    if (mesh_.elementArraySize() != 0)
        glDrawElements(GL_TRIANGLES, mesh_.elementArraySize(), GL_UNSIGNED_INT, (void*)0);
    else
        glDrawArrays(GL_TRIANGLES, 0, mesh_.totalVert());
}
