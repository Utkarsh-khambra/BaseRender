#include <iostream>
#include <GLFW/glfw3.h>
#include "../include/Input.hpp"
#define KEYBOARD          1
#define CURSOR            2
#define CURSOR_HIDDEN     3
#define CURSOR_DISABLED   4
#define MOUSE_KEY         5
Input::Input () {}
Input::~Input () {}

void Input::inputForWindow (Window* window)
{
    inputOnWindow = window;
}


// Write now doesnt support keyboard and mouse button input tyring off
void Input::setInputMode (int mode, int value)
{
    if (mode == KEYBOARD)
        glfwSetInputMode(inputOnWindow, GLFW_STICKY_KEYS, GL_TRUE);
    if (mode == CURSOR)
        glfwSetInputMode(inputOnWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    if (mode == CURSOR_HIDDEN)
        glfwSetInputMode(inputOnWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    if (mode == CURSOR_HIDDEN)
        glfwSetInputMode(inputOnWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (mode == MOUSE_KEY)
        glfwSetInputMode(inputOnWindow, GLFW_STICKY_MOUSE_KEYS, GL_TRUE);
}

int Input::getKey (int key)
{
    glfwGetKey(inputOnWindow, key);
}

void Input::getCurPos (double* xpos, double* ypos)
{
    glfwGetCursorpos(inputOnWindow, xpos, ypos);
}

void Input::setCurPos (int x, int y)
{
    glfwSetCursorPos(inputOnWindow, x, y);
}
