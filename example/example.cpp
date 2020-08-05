#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <array>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "../include/Window.hpp"
#include "../include/Input.hpp"
#include "../include/Camera.hpp"
#include "../include/CameraFPS.hpp"
#include "../include/Shader.hpp"
#include "../include/Program.hpp"
#include "../include/Object.hpp"
#include "../include/LoadObj.hpp"
#include "../include/Scene.hpp"

void render (Scene& s1, Window& w1);
int main()
{
    Scene sc1;
    Window win(1024,768, "Hello");
    try{
        win.intialize();
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << '\n';
    }
    win.makeCurrent();
    CameraFPS cam;
    cam.setPosition(glm::vec3(0,0,8));
    cam.lookAt(glm::vec3(0,0,0));
    Shader s1("../phong.glsl");
    Program p1;
    p1.bindShader(s1, ALL);
    p1.makeProgram();
    p1.sharedUniform("Matrices", 0);
    GLuint MatrixBuffer = p1.makeSharedUniformBuffer(64, 0);
    p1.fillUniformBuffer(MatrixBuffer, glm::value_ptr(cam.cameraMatrix()), 64, 0);

    Object obj;
    LoadObj("../man.obj", obj);
    GLuint vao;
    glGenVertexArrays(1, &vao);
    obj.setup(vao, GL_STATIC_DRAW, p1);
    sc1.addObjcet(obj);
    sc1.addCamera(cam);
    // glBindVertexArray (vao);
    render (sc1, win);
}


void render (Scene& s1, Window& w1)
{
    while (!w1.isClosed()) {

        glEnable(GL_DEPTH_TEST);
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        if (Input::isPressed(w1, ESCAPE))
            w1.setWindowClosed();
        s1.camera->update(w1);
        glm::mat4 mat= s1.camera->cameraMatrix();
        glUniformMatrix4fv(glGetUniformLocation(3, "Camera"), 1, GL_FALSE, glm::value_ptr(mat));
        s1.head->render();
        Input::setCurPos(w1, 0,0);
        glfwSwapBuffers(w1.winPtr());
        Input::pollEvents();
    }
}
