/*
  Input.hpp
  Date-12/03/2019
*/
#pragma once
class Window;
class Input{
public:
    Input ();
    ~Input ();
    inline void inputForWindow (Window* window);
    /* Mode should be one of the following
       KEYBOARD
       CURSOR
       CURSOR_HIDDEN
       CURSOR_DISABLED
       MOUSE_KEY */
    void setInputMode (int Mode)
    inline int getKey (int key);
    inline void getCurPos (double* xpos, double* ypos);
    inline void setCurPos (int x, int y);
private:
    Window* inputOnWindow = NULL;
};
