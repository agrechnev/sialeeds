#pragma once
// By Oleksiy Grechnyev

namespace MotokoGL {

/// Material properties
struct Material{

    /// Constructor
    Material(const glm::vec3 & ambient,
             const glm::vec3 & diffuse,
             const glm::vec3 & specular,
             const glm::vec3 & emission,
             float shininess) :
        ambient(ambient),
        diffuse(diffuse),
        specular(specular),
        emission(emission),
        shininess(shininess) {}

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 emission;
    float shininess;
};
}
