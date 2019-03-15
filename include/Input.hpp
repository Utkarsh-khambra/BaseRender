/*
  Input.hpp
  Date-12/03/2019
*/
#pragma once
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
    int getKey (Window& window,int key);
    void getCurPos (Window& window,double* xpos, double* ypos);
    void setCurPos (Window& window,int x, int y);

}
