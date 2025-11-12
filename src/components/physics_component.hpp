#pragma once

struct PhysicsComponent {
    glm::vec3 velocity = glm::vec3(0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f);
    GLfloat mass;
    GLfloat radius;
};