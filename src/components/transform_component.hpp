#pragma once
#include "../config.hpp"

struct TransformComponent {
    glm::vec3 position;
    glm::vec3 eulers;
    glm::vec3 scale;
    glm::vec2 shearX;
    glm::vec2 shearY;
    glm::vec2 shearZ;
};