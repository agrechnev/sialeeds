#include <cmath>

#include "YPRCamera.h"
namespace MotokoGL {

void YPRCamera::move(float fb, float rl, float ud)
{
    updateAngles();
    pos += float(sensitivity)*(fb*front + rl*right + ud*up);
}

void YPRCamera::updateAngles()
{
    using namespace std;
    using namespace glm;
    // Check pitch
    if (pitch > 89.0f)
        pitch = 89.0f;
    else if (pitch < -89.0f)
        pitch = -89.0f;
    // Set the direction, target and up
    front = vec3(
                cos(radians(pitch))*cos(radians(yaw)),
                sin(radians(pitch)),
                cos(radians(pitch))*sin(radians(yaw))
                );
    // Recalculate up (needed for movement)
    right = normalize(cross(front, worldUp));
    up = normalize(cross(right, front));
}

}
