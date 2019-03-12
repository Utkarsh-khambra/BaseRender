#include <iostream>
#include <string>
#include <GLFW/glfw3.h>


Window::Window (int width_, int height_, std::string title_):width(width_),
                                                             height(height_),
                                                             title(title_) {}
void Window::intialize ()
{
    if (!glfwInit()) {
        glfwTerminate();
        throw std::runtime_error("GLFW failed to initialzie");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    windowptr = glfwCreateWindow (width, height, title, NULL, NULL);
}

void Window::makeCurrent ()
{
    glfwMakeCurrent(windowptr);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        throw std::runtime_error("GLEW failed to load GL");
    }
}

void Window::update ()
{

}
