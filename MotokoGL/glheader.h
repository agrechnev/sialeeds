#pragma once
// By Oleksiy Grechnyev
// All OpenGL headers we use

// GLEW
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
//#define GLEW_STATIC
#include <GL/glew.h>
#endif

// GLFW (after GLEW)
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
