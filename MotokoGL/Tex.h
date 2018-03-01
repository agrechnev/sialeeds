#pragma once
// By Oleksiy Grechnyev

#include <string>

#include "./glheader.h"

namespace MotokoGL {

/// Texture operations
class Tex
{
private: //====== Constructor
    /// Private constructor
    Tex();

public:  //======= Methods
    /// Load texture from file with SOIL
    static Tex fromFile(const std::string & fileName);

    /// Bind as texture #index
    void bind(unsigned index) const{
        glActiveTexture(GL_TEXTURE0 + index);
        glBindTexture(GL_TEXTURE_2D, tex);
    }

    GLuint getTex() const{
        return tex;
    }

private: //======= Data
    /// The texture
    GLuint tex;

    /// Width and height
    int w = 0, h = 0;
};

}
