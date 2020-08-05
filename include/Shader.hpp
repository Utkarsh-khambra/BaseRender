#pragma once
#define MAX_ATTRIBUTES 4
struct Shader {
    Shader ();
    ~Shader ();
    Shader (std::string shaderPath);
    GLuint vertex_shader;
    GLuint frag_shader;
    GLuint attribLocation[MAX_ATTRIBUTES];
    GLushort availableShaders;
};

void LoadShader (Shader& shader, std::string shaderPath);
