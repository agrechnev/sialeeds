#include <iostream>


#include "MotokoError.h"

#include "Window.h"

namespace MotokoGL {
    Window::Window(int w, int h, const std::string &title, int vMajor, int vMinor, bool hidden) {
        // Init GLFW
        glfwInit();

        // Error callback should be set early
        glfwSetErrorCallback([](int e, const char *msg) {
            std::cerr << "GLFW error : " << e << msg << std::endl;
        });

        // Set parameters
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, vMajor);  // Version, 3.3 is default
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, vMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Do we need it ?

        if (hidden)
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        // Create GLFW window
        win = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
        if (win == nullptr)
            throw MotokoError("Cannot create GLFW window !");

        glfwMakeContextCurrent(win); // Doesn't work without it ;)

        // Init GLEW
#ifndef __APPLE__
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
            throw MotokoError("Cannot initialize GLEW !");
#endif

        // From now on
        // Set viewport (should be equal to the window size)
        glfwGetFramebufferSize(win, &width, &height);

        // The first OpenGL function call: init viewport
        glViewport(0, 0, width, height);
    }

    double Window::time() {
        using namespace std::chrono;
        auto time = high_resolution_clock::now();
        return duration<double>(time - time0).count();  // time difference
    }

}
