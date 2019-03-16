/*
  Input.hpp
  Date-12/03/2019
*/
#pragma once
#define ESCAPE            GLFW_KEY_ESCAPE
#define UP                GLFW_KEY_UP
#define DOWN              GLFW_KEY_DOWN
#define LEFT              GLFW_KEY_LEFT
#define RIGHT             GLFW_KEY_RIGHT
#define LCTRL             GLFW_KEY_LEFT_CONTROL
#define RCTRL             GLFW_KEY_RIGHT_CONTROL
#define KEYBOARD          1
#define CURSOR            2
#define CURSOR_HIDDEN     3
#define CURSOR_DISABLED   4
#define MOUSE_KEY         5

class Window;
namespace Input {
    /* Mode should be one of the following
       KEYBOARD
       CURSOR
       CURSOR_HIDDEN
       CURSOR_DISABLED
       MOUSE_KEY */
    void setInputMode (Window& window, int Mode);
    bool isPressed (Window& window, int key);
    bool isReleased (Window& window, int Key);
    void getCurPos (Window& window,double* xpos, double* ypos);
    void setCurPos (Window& window,int x, int y);
    void pollEvents ();
}
