#pragma once
// By Oleksiy Grechnyev

#include "./SimpleCamera.h"

namespace MotokoGL {

/// Yaw Pitch Roll camera
class YPRCamera : public SimpleCamera
{
public: //===== Methods

    virtual glm::mat4 matrixView() override {
        updateAngles();
        target = pos + front;
        return SimpleCamera::matrixView();
    }

    /// Move the camera forward-back, right-left or up-down
    void move(float fb, float rl, float ud);

protected: //===== Methods

    void updateAngles();

protected: //===== Fields
    glm::vec3 front;  // The diection the camera is facing
    glm::vec3 right;  // The right direction

public: //===== Fields
    /// Angles (no roll yet)
    double yaw = -90.0;
    double pitch = 0.0;

    /// Camera sensitivity
    double sensitivity = 1.0;

    /// The world up vector
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
};
}

