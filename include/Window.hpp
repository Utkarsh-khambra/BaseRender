#pragma once


class Window{
public:
    Window (int width_, int height, std::string title_);
    ~Window ();
    void intialize ();
    void update ();
    void resize ();
    void makeCurrent ();
private:
    int width;
    int height;
    std::string title;
    GLFWwindow* windowptr = NULL;
};
