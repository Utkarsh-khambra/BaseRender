#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include "../include/Shader.hpp"

Shader::Shader () {}

Shader::Shader (std::string shaderPath)
{
    LoadShader(*this, shaderPath);
}

void LoadShader (Shader& shader, std::string shaderPath)
{
    enum shaderType{NONE = -1, VERTEX, FRAGMENT};
    std::fstream stream(shaderPath);
    std::stringstream ss[2];
    std::string line;
    int type = NONE;
    int count1 = 0;
    while (std::getline(stream, line)){
        if (line.find("shader") != std::string::npos){
            if (line.find("vertex") != std::string::npos)
                type = VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = FRAGMENT;
        }
        else{
            ss[type] << line <<'\n';

            if (line.find("layout(location") != std::string::npos) {
              int count = 0;
              std::size_t prev = 0, pos;
              while ((pos = line.find_first_of("() ", prev)) != std::string::npos)
              {
                  if (pos>prev && count == 3){
                      if (count1 > MAX_ATTRIBUTES)
                          std::cerr << "Too many attributes increase max attribs" << '\n';
                      shader.attribLocation[count1] = (GLuint)stoi(line.substr(prev, pos-prev));
                      shader.availableShaders = count1 + 1;
                      ++count1;
                      break;
                  }
                  prev = pos+1;
                  ++count;
              }
            }

        }
    }
    GLint Result = GL_FALSE;
    int InfoLogLength;
    shader.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    shader.frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    std::cout << "Compiling shade :" << shaderPath << '\n';
    //Compile vertex shader
    std::string temp = ss[0].str();
    const char* temp1 = temp.c_str();
    glShaderSource(shader.vertex_shader, 1, &temp1, NULL);
    glCompileShader(shader.vertex_shader);

    //Check vertex shader
    glGetShaderiv(shader.vertex_shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shader.vertex_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> vertex_shaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shader.vertex_shader, InfoLogLength, NULL, &vertex_shaderErrorMessage[0]);
        std::cout << vertex_shaderErrorMessage.data() << '\n';
    }

    //Compile Fragment shader
    std::cout << "Compiling shader :" << shaderPath <<'\n';
    std::string temp2 = ss[1].str();
    const char* temp3 = temp2.c_str();
    glShaderSource(shader.frag_shader, 1, &temp3, NULL);
    glCompileShader(shader.frag_shader);

    //Check fragnment shader
    glGetShaderiv(shader.frag_shader, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shader.frag_shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0){
        std::vector<char> fragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(shader.frag_shader, InfoLogLength, NULL, &fragmentShaderErrorMessage[0]);
        std::cout << fragmentShaderErrorMessage.data() << '\n';
    }
}

Shader::~Shader () {}
