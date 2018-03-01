//
// Created by  Oleksiy Grechnyev on 5/10/2017.
//

#pragma once

#include "./glheader.h"

namespace MotokoGL {
    /// Light source properties
    struct Light {
        Light(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
                : position(position),
                  ambient(ambient),
                  diffuse(diffuse),
                  specular(specular) {}

        /// Source position
        glm::vec3 position;

        /// Light properties
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

}

