#include <iostream>

#include "./stb_image.h"

#include "./MotokoError.h"

#include "./Tex.h"

namespace MotokoGL {

    Tex::Tex() {
        // Create and bind texture objects
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        // Set wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Set filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Unbind me
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // stb_image version
    Tex Tex::fromFile(const std::string &fileName) {
        Tex t;

        // Bind
        glBindTexture(GL_TEXTURE_2D, t.tex);
        int bpp;

        // Load image from a file with SOIL
        unsigned char *image = stbi_load(fileName.c_str(), &t.w, &t.h, &bpp, 3);

        if (image == NULL)
            throw MotokoError("Tex::fromFile() : Cannot load image " + fileName);

        // To avoid segfaults, WTF ???
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
        glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
        glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

        // Set up the image
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t.w, t.h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Free memory and unbind
        stbi_image_free(image);
//        free(image2);
        glBindTexture(GL_TEXTURE_2D, 0);

        return t;
    }
//==============================================================

}
