#pragma once
#include "../config.hpp"

struct CameraComponent {
    glm::vec3 up;
    glm::mat4 projection;
    glm::mat4 view;
    float FOV, nearPlane, farPlane;
    float nearPlane_height, aspect_ratio;

    float speed;
    float sensitivity;

    bool firstClick = true;
};