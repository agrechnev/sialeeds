#pragma once
// By Oleksiy Grechnyev

#include <chrono>
#include <string>

#include "./glheader.h"

namespace MotokoGL{
/// OpenGL Window
class Window
{
public: //======== Methods
    /// Constructor
    Window(int w, int h, const std::string & title, int vMajor = 3, int vMinor = 3, bool hidden=false);

    /// Destructor
    ~Window() {
        glfwTerminate(); // Stop openGL
    }

    /// Swap the buffers
    void swapBuffers() {
        glfwSwapBuffers(win);
    }

    /// Should this window close?
    bool shouldClose() const{
        return glfwWindowShouldClose(win);
    }

    int getWidth() const
    {
        return width;
    }

    int getHeight() const
    {
        return height;
    }

    /// Get time in seconds since the window was created
    double time();

    GLFWwindow * getWin() {
        return win;
    }

    int getKey(int key){
        return glfwGetKey(win, key);
    }

private: //========= Fields
    /// The Window pointer
    GLFWwindow * win = nullptr;

    /// Viewport Width and height
    int width=0, height=0;

    /// The start time
    std::chrono::time_point<std::chrono::high_resolution_clock> time0 =
            std::chrono::high_resolution_clock::now();

};
}
