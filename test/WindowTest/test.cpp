#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include "../../include/Window.hpp"

int main()
{
    Window w1(1024,768,"Test");
    try{
        w1.intialize();
    }
    catch(std::runtime_error& e){
        std::cerr << e.what() << '\n';
    }
    return 0;
}
