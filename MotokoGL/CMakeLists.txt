cmake_minimum_required(VERSION 3.0)
project (MotokoGL)

set (CMAKE_CXX_STANDARD 14)

# Source files
set (SOURCE_FILES
      ./glheader.h
      ./MotokoError.h
      ./Window.cpp ./Window.h
      ./ShaderProg.cpp ./ShaderProg.h
      ./IVao.h
      ./Vao.h ./Vao.cpp
      ./Tex.h ./Tex.cpp
      ./SimpleCamera.h
      ./YPRCamera.h ./YPRCamera.cpp
      ./Material.h
      ./MaterialT.h
      ./MotokoGL.h
      ./Light.h
        ./stb_image.h ./stb_image.cpp
        )

add_library(MotokoGL ${SOURCE_FILES})
