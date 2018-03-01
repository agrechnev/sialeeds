#include <iostream>
#include <thread>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <chrono>

#include <opencv2/opencv.hpp>

#include "MotokoGL.h"

#include "./cubevao.h"

using namespace std;
using namespace std::chrono;
using namespace MotokoGL;
using namespace glm;
using namespace cv;

//=============================================================
inline GLfloat funCos(GLfloat x) {
    return 0.5f * (cosf(x) + 1);
}
//float random number between 0.0f and 1.0f
inline float randf() {
    return (float) rand() / (float) RAND_MAX;
}
// Random unit 3-vector with spherical distribution
static glm::vec3 randUV3() {
    float t = acos(2 * randf() - 1);
    float p = M_PI * 2 * randf();
    glm::vec3 result(sin(t) * cos(p), sin(t) * sin(p), cos(t));
    return result;
}
//=============================================================
int main() {
    srand(time(NULL));
    Window window(1000, 750, "Goblin OpenGL Test 2", 3, 3, false);  // The Window
    const float aspectRatio = 1.0f * window.getWidth() / window.getHeight(); // Need for the camera
    int width = window.getWidth();
    int height = window.getHeight();
    glEnable(GL_DEPTH_TEST);
    ShaderProg prog = ShaderProg::fromFiles("shaders/vert.glsl", "shaders/frag.glsl"); // Program
    Tex tex1 = Tex::fromFile("common_textures/container.jpg");  // Texture 1
    Tex tex2 = Tex::fromFile("common_textures/awesomeface.png");  // Texture 2
    Vao cubeVao = createCube();  // Cube VAO
    SimpleCamera camera;  // Camera
//    YPRCamera camera;  // Camera
    camera.aspect = aspectRatio;
//    camera.sensitivity = 3.0;
    //-------------------------------------------
    // Cube positions
    vec3 cubePositions[] = {
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f, 3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f, 2.0f, -2.5f),
            glm::vec3(1.5f, 0.2f, -1.5f),
            glm::vec3(-1.3f, 1.0f, -1.5f)
    };
    // Random rotation axes and velocities
    constexpr int NCUBE = 10;
    vec3 cubeAxes[NCUBE];
    float cubeAV[NCUBE]; // Angular velocities
    float cubeMV[NCUBE]; // Mix velocities
    // Loop over 10 cubes
    for (int cube = 0; cube < NCUBE; cube++) {
        cubeAV[cube] = 4.0f * randf() - 2.0f; // Between -2 and 2 RADIAN / time unit
        cubeMV[cube] = 3.0f * randf() + 1.0f;
        cubeAxes[cube] = randUV3(); // Random unit vector
    }
    //-------------------------------------------
    // OpenCV frame
    Mat frame(height, width, CV_8UC3, Scalar(0, 255, 255));
    namedWindow("Goblin OpenCV 2");

    //-------------------------------------------
    // GLFW game loop
    using DSeconds = duration<double>;
    auto time1 = high_resolution_clock::now();
    int frameCount = 0;
    while (!window.shouldClose()) {
        glfwPollEvents();
        double t = window.time(); // Time in double seconds
        if (window.getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS)
            break;  // Exit on ESC

        // Clear screen
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // RGBA
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Program and texture
        prog.use();
        tex1.bind(0);  // Set texture 1
        glUniform1i(prog.loc("uTex1"), 0);
        tex2.bind(1);  // Set texture 2
        glUniform1i(prog.loc("uTex2"), 1);

        // Camera matrix
        mat4 cam = camera.matrix();
        // Draw 10 cubes
        for (int i = 0; i < NCUBE; i++) {
            // Texture mix: fun
            glUniform1f(prog.loc("uMix"), funCos(t * cubeMV[i]));

            // Model matrix
            mat4 model;
            model = translate(model, cubePositions[i]);
            model = rotate(model, float(t * cubeAV[i]), cubeAxes[i]); // Rotate

            prog.setMatCM(cam, model); // Set matrices
            cubeVao.draw(); // Draw
        }
        window.swapBuffers(); // The actual draw

        // Read pixels
        glReadPixels(0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, frame.data);
        flip(frame, frame, 0);

        // Draw opencv
        imshow("Goblin OpenCV 2", frame);
        if (27 == waitKey(1))
            break;

        // Fps check
        frameCount++;
        auto time2 = high_resolution_clock::now();
        double timeDiff = DSeconds(time2 - time1).count();
        if (timeDiff > 5.0) {
            cout << "FPS = " << frameCount/timeDiff << endl;
            time1 = time2;
            frameCount = 0;
        }
//        this_thread::sleep_for(chrono::milliseconds(15));
    }
    cout << "See ya soon !" << endl;
    return 0;
}
