#pragma once
// By Oleksiy Grechnyev

#include "./glheader.h"

namespace MotokoGL {
/// The simple camera implementation with target, position,
class SimpleCamera {
public: //======== Methods

    // Create the camera matrix (proj*view) using our data
    virtual glm::mat4 matrix(){
        using namespace glm;
        mat4 view = matrixView();  // View matrix
        mat4 proj = matrixProj(); // Projection (perspective) matrix
        return proj*view;
    }

    // Create the view matrix
    virtual glm::mat4 matrixView(){
        using namespace glm;
        return lookAt(pos, target, up);
    }

    // Create the proj matrix
    virtual glm::mat4 matrixProj(){
        using namespace glm;
        return perspective(glm::radians(fovy), aspect, zMin, zMax);
    }

public: //======== Getters + setters

    glm::vec3 getTarget() const
    {
        return target;
    }

    void setTarget(const glm::vec3 &value)
    {
        target = value;
    }


    glm::vec3 getUp() const
    {
        return up;
    }

    void setUp(const glm::vec3 &value)
    {
        up = value;
    }


public: //======== fields
    /// Camera position
    glm::vec3 pos{0.0f, 0.0f, 4.0f};

    /// Aspect ratio
    GLfloat aspect = 1.0f;

    /// Min and max Z
    GLfloat zMin = 0.1f, zMax = 100.0f;

    /// Field-Of-View Y in degrees
    GLfloat fovy = 45.0f;

protected: //======= fields
    /// Camera target
    glm::vec3 target{0.0f, 0.0f, 0.0f};

    /// The up-vector
    glm::vec3 up{0.0f, 1.0f, 0.0f};
};


}
