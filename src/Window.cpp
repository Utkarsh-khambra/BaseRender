#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#define NDEBUG
#include <cassert>
#include "../include/Window.hpp"


Window::Window (int width_, int height_, std::string title_):width(width_),
                                                             height(height_),
                                                             title(title_)
{
    if (width < 0)
        throw std::invalid_argument("Width is negative");
    if (height < 0)
        throw std::invalid_argument("Height is negative");
}
void Window::intialize ()
{
    assert(windowptr == NULL);
    if (!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("GLFW failed to initialzie");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    windowptr = glfwCreateWindow (width, height, title.c_str(), NULL, NULL);
}

void Window::makeCurrent ()
{
    assert(windowptr != NULL);
    glfwMakeContextCurrent(windowptr);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("GLEW failed to load GL");
    }
}

void Window::update ()
{
    glEnable(GL_DEPTH_TEST);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::resize ()
{

}

Window::~Window ()
{
    glfwDestroyWindow(windowptr);
    glfwTerminate();

}

GLFWwindow* Window::winPtr ()
{
    return windowptr;
}
