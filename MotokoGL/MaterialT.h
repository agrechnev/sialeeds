#pragma once
// By Oleksiy Grechnyev

#include "./Tex.h"

namespace MotokoGL {

/// Material properties with textures
struct MaterialT{

    /// Constructor
    MaterialT(const Tex & ambient,
              const Tex & diffuse,
              const Tex & specular,
              const Tex & emission,
              float shininess,
              int flags) :
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        emission(emission),
        shininess(shininess),
        flags(flags){}



    /// Textures
    Tex ambient;
    Tex diffuse;
    Tex specular;
    Tex emission;

    /// Shininess parameter
    float shininess;

    /// The flags (or operation)
    int flags;

    static constexpr int F_AMBIENT = 1;
    static constexpr int F_DIFFUSE = 2;
    static constexpr int F_SPECULAR = 4;
    static constexpr int F_EMISSION = 8;
};
}
