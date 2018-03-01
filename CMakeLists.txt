cmake_minimum_required(VERSION 3.0)
project (sialeeds)

set (CMAKE_CXX_STANDARD 14)

# Find GLFW, GLEW
FIND_LIBRARY(GLFW_LIB NAMES glfw glfw3 glfw.3.2)
message("GLFW_LIB = ${GLFW_LIB}")
if(NOT DEFINED ${APPLE})
    FIND_LIBRARY(GLEW_LIB NAMES glew GLEW glew32)
endif()
message("GLEW_LIB = ${GLEW_LIB}")

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(OPENGL_INCLUDE_DIR)
message("OPENGL_gl_LIBRARY = ${OPENGL_gl_LIBRARY}")
message("OPENGLu_gl_LIBRARY = ${OPENGL_glu_LIBRARY}")
message("OPENGL_LIBRARIES = ${OPENGL_LIBRARIES}")
message("OPENGL_INCLUDE_DIR = ${OPENGL_INCLUDE_DIR}")

# All GL libs
set(GL_LIBS  ${GLEW_LIB} ${GLFW_LIB} ${OPENGL_LIBRARIES})
message("GL_LIBS = ${GL_LIBS}")

# Find OpenCV
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Build MotokoGL library
add_subdirectory(MotokoGL)
include_directories(MotokoGL )

# Build all targets
add_subdirectory(t0)
add_subdirectory(t1)
add_subdirectory(t2)
