#pragma once

// By Oleksiy Grechnyev
// Fatal Error for MotokoGL

#include <iostream>
#include <string>

#include "./glheader.h"


namespace MotokoGL{

//=============================================================

inline void fatal(const std::string & msg){
    std::cerr << msg << std::endl;
    glfwTerminate();
    exit(-1);
}
//=============================================================
inline void fatal2(const std::string & msg1, const std::string & msg2){
    std::cerr << msg1 << " : " << msg2 << std::endl;
    glfwTerminate();
    exit(-1);
}
}

