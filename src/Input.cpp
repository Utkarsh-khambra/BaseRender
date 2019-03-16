#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/Input.hpp"
#include "../include/Window.hpp"
namespace Input {
// Write now doesnt support keyboard and mouse button input tyring off
    void setInputMode (Window& window,int mode)
    {
        if (mode == KEYBOARD)
            glfwSetInputMode(window.winPtr(), GLFW_STICKY_KEYS, GL_TRUE);
        if (mode == CURSOR)
            glfwSetInputMode(window.winPtr(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        if (mode == CURSOR_HIDDEN)
            glfwSetInputMode(window.winPtr(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if (mode == CURSOR_HIDDEN)
            glfwSetInputMode(window.winPtr(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        // if (mode == MOUSE_KEY)
        //     glfwSetInputMode(window.winPtr(), GLFW_STICKY_MOUSE_KEYS, GL_TRUE);
    }

    void getCurPos (Window& window,double* xpos, double* ypos)
    {
        glfwGetCursorPos(window.winPtr(), xpos, ypos);
    }

    void setCurPos (Window& window,int x, int y)
    {
        glfwSetCursorPos(window.winPtr(), x, y);
    }

    bool isPressed (Window& window, int key)
    {
        if (glfwGetKey (window.winPtr(), key) == GLFW_PRESS)
            return true;
        else
            return false;
    }

    bool isReleased (Window& window, int key)
    {
        if (glfwGetKey(window.winPtr(), key) == GLFW_RELEASE)
            return true;
        else
            return false;
    }

    void pollEvents ()
    {
        glfwPollEvents();
    }
}
