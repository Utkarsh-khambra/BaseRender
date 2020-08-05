#include <iostream>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/Shader.hpp"
#include "../include/Program.hpp"

Program::Program ()
{
    for (int i = 0; i < MAX_UNIFORM_BLOCKS; ++i)
        uniformBlockIndex[i] = GL_INVALID_INDEX;
}

void Program::makeProgram ()
{
    if (attachedShaders.size() < 2)
        std::cerr << "No shaders are bound or not enough shader are bound" << '\n';
    else{
        GLint Result = GL_FALSE;
        int InfoLogLength = 0;
        std::cout << "Linking Program" << '\n';
        programID = glCreateProgram();
        glAttachShader(programID, attachedShaders[VERTEX]->vertex_shader);
        glAttachShader(programID, attachedShaders[FRAGMENT]->frag_shader);
        glLinkProgram(programID);

        // Check Program
        glGetProgramiv(programID, GL_LINK_STATUS, &Result);
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(programID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            std::cout << ProgramErrorMessage.data() << '\n';
        }

        glDetachShader(programID, attachedShaders[VERTEX]->vertex_shader);
        glDetachShader(programID, attachedShaders[FRAGMENT]->frag_shader);
    }
}

void Program::bindShader (Shader& shader, GLuint whichShaderType)
{
    switch (whichShaderType) {
      case VERTEX: attachedShaders[VERTEX] = &shader;
          break;
      case FRAGMENT: attachedShaders[FRAGMENT] = &shader;
          break;
      case ALL: attachedShaders[VERTEX] = &shader;
          attachedShaders[FRAGMENT] = &shader;
          break;
    }
}

GLuint Program::id ()
{
    return programID;
}

void Program::setUniform (std::string name, std::vector<GLfloat> values)
{
    GLuint temp = glGetUniformLocation(programID, name.c_str());
    auto x = std::find(uniforms.begin(), uniforms.end(), temp);
    if (x == uniforms.end()){
        uniforms.push_back(temp);
        switch (values.size()) {
            case 1: glUniform1f(uniforms.back(), values[0]);
                break;
            case 2: glUniform2f(uniforms.back(), values[0], values[1]);
                break;
            case 3: glUniform3f(uniforms.back(), values[0], values[1], values[2]);
                break;
            case 4: glUniform4f(uniforms.back(), values[0], values[1], values[2], values[3]);
                break;
        }
    }
    else{
        switch (values.size()) {
            case 1: glUniform1f(*x, values[0]);
                break;
            case 2: glUniform2f(*x, values[0], values[1]);
                break;
            case 3: glUniform3f(*x, values[0], values[1], values[2]);
                break;
            case 4: glUniform4f(*x, values[0], values[1], values[2], values[3]);
                break;
        }
    }
}

void Program::setUniformMatrix2 (std::string name, glm::mat2* mat)
{
    GLuint temp = glGetUniformLocation(programID, name.c_str());
    auto x = std::find(uniforms.begin(), uniforms.end(), temp);
    if (x == uniforms.end()){
        uniforms.push_back(temp);
        glUniformMatrix2fv(uniforms.back(), 1, GL_FALSE, glm::value_ptr(*mat));
    }
    else{
        glUniformMatrix2fv(*x, 1, GL_FALSE, glm::value_ptr(*mat));
    }


}
void Program::setUniformMatrix3 (std::string name, glm::mat3* mat)
{
    GLuint temp = glGetUniformLocation(programID, name.c_str());
    auto x = std::find(uniforms.begin(), uniforms.end(), temp);
    if (x == uniforms.end()){
        uniforms.push_back(temp);
        glUniformMatrix3fv(uniforms.back(), 1, GL_FALSE, glm::value_ptr(*mat));
    }
    else{
        glUniformMatrix3fv(*x, 1, GL_FALSE, glm::value_ptr(*mat));
    }
}
void Program::setUniformMatrix4 (std::string name, glm::mat4& mat)
{
    GLuint temp = glGetUniformLocation(programID, name.c_str());
    auto x = std::find(uniforms.begin(), uniforms.end(), temp);
    if (x == uniforms.end()){
        uniforms.push_back(temp);
        glUniformMatrix4fv(uniforms.back(), 1, GL_FALSE, glm::value_ptr(mat));
    }
    else{
        glUniformMatrix4fv(*x, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void Program::sharedUniform (std::string uniformBlockName, GLuint bindingIndex)
{
    if (uniformBlockIndex[MAX_UNIFORM_BLOCKS - 1] != GL_INVALID_INDEX){
        std::cerr << "Maximum uniform block capacity reached" << '\n';
        return;
        // return false;
    }

    for (int i = 0; i < MAX_UNIFORM_BLOCKS; ++i){
        if (uniformBlockIndex[i] == GL_INVALID_INDEX){
            uniformBlockIndex[i] = glGetUniformBlockIndex(programID, uniformBlockName.c_str());
            if (uniformBlockIndex[i] == GL_INVALID_INDEX)
                std::cerr << "No such uniform block found for this program" << '\n';
            else{
                glUniformBlockBinding(programID, uniformBlockIndex[i], bindingIndex);
                std::cout << uniformBlockIndex[i] << '\n';
                std::cout << "Bounded the uniform block buffer correctly" << '\n';
                // return true;
                break;
            }
        }
    }
}

GLuint Program::makeSharedUniformBuffer (std::size_t bufferSize, GLuint bindingIndex)
{
    // if (ubo.find(bufferName) != ubo.end()){
    //     std::cerr << "Warning: A buffer with same name already exists" << '\n';
    //     return;
    // }
    GLuint temp;
    glGenBuffers(1, &temp);
    // ubo.insert(std::pair<std::string, GLuint>(bufferName, temp));
    glBindBuffer(GL_UNIFORM_BUFFER, temp);
    glBufferData(GL_UNIFORM_BUFFER, bufferSize, NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, bindingIndex);
    glBindBufferRange(GL_UNIFORM_BUFFER, bindingIndex, temp, 0, bufferSize);// Bindes whole buffer
    return temp;
}

void Program::fillUniformBuffer (GLuint bufferRef, const GLfloat* data, std::size_t dataSize, GLuint offset)
{
    // auto it = ubo.find(bufferName);
    // if (it == ubo.end()){
    //     std::cerr << "Error:No such buffer exist" << '\n';
    //     return;
    // }
    // int temp = it->second;
    glBindBuffer(GL_UNIFORM_BUFFER, bufferRef);
    glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, data);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
