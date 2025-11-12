#include "motion_system.hpp"

void MotionSystem::update(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt)
{

    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        TransformComponent & trasnformComponent = transformComponents[ID];
        PhysicsComponent & physicsComponent = physicsComponents[ID];

        trasnformComponent.position += physicsComponent.velocity * dt;
    }
    
    return;
}

void MotionSystem::updateGravity(
    std::vector<TransformComponent> &transformComponents,
    std::vector<PhysicsComponent> &physicsComponents,
    float dt
)
{
    GLfloat G = 6.6743e-11; // m^3 kg^-1 s^-2 (gravitational constant)
    GLfloat scale = 1e11;    // scale factor to adjust gravitational effect
    G *= scale;

    GLfloat epsilon = 0.1f * 0.1f; // Minimum distance to avoid singularity e^2

    std::vector<glm::vec3> accelerations(physicsComponents.size(), glm::vec3(0.0f));

    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        TransformComponent & trasnformComponent = transformComponents[ID];
        PhysicsComponent & physicsComponent = physicsComponents[ID];

        glm::vec3 totalAcceleration = glm::vec3(0.0f);
        for (GLuint otherID = 0; otherID < physicsComponents.size(); ++otherID)
        {
            TransformComponent & otherTransformComponent = transformComponents[otherID];
            PhysicsComponent & otherPhysicsComponent = physicsComponents[otherID];

            glm::vec3 direction = otherTransformComponent.position - trasnformComponent.position;
            GLfloat distanceSquared = glm::dot(direction, direction) + epsilon; // Avoid division by zero

            GLfloat distance = glm::sqrt(distanceSquared);
            glm::vec3 forceDirection = direction / distance;

            // Gravitational force magnitude
            GLfloat forceMagnitude = (G * physicsComponent.mass * otherPhysicsComponent.mass) / distanceSquared;

            // Acceleration due to this force
            glm::vec3 acceleration = (forceMagnitude / physicsComponent.mass) * forceDirection;

            totalAcceleration += acceleration;
        }
        accelerations[ID] = totalAcceleration;
    }

    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        PhysicsComponent & physicsComponent = physicsComponents[ID];
        physicsComponent.velocity += accelerations[ID] * dt;
    }
}