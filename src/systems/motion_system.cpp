#include "motion_system.hpp"

void MotionSystem::updateCPU(
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

void MotionSystem::updateGPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt)
{
    
}

void MotionSystem::updateGravity(
    std::vector<TransformComponent> &transformComponents,
    std::vector<PhysicsComponent> &physicsComponents,
    float dt
)
{
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

void MotionSystem::updateColision(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt) 
{
    std::vector<glm::vec3> velocities(physicsComponents.size(), glm::vec3(0.0f));
    std::vector<bool> hasCollided(physicsComponents.size(), false);

    for (size_t ID = 0; ID < physicsComponents.size(); ID++)
    {
        TransformComponent & trasnformComponent = transformComponents[ID];
        PhysicsComponent & physicsComponent = physicsComponents[ID];

        for (size_t otherID = ID + 1; otherID < physicsComponents.size(); otherID++)
        {
            TransformComponent & otherTransformComponent = transformComponents[otherID];
            PhysicsComponent & otherPhysicsComponent = physicsComponents[otherID];

            glm::vec3 direction = otherTransformComponent.position - trasnformComponent.position;
            GLfloat distance = glm::length(direction);

            if (distance < (physicsComponent.radius + otherPhysicsComponent.radius))
            {
                glm::vec3 normalDirection = glm::normalize(direction);
                glm::vec3 tangentDirection = glm::vec3(-normalDirection.y, normalDirection.x, 0.0f);

                GLfloat v1n = glm::dot(physicsComponent.velocity, normalDirection);
                GLfloat v1t = glm::dot(physicsComponent.velocity, tangentDirection);
                GLfloat v2n = glm::dot(otherPhysicsComponent.velocity, normalDirection);
                GLfloat v2t = glm::dot(otherPhysicsComponent.velocity, tangentDirection);

                GLfloat v1nAfter = (v1n * (physicsComponent.mass - otherPhysicsComponent.mass) + 2.0f * otherPhysicsComponent.mass * v2n) / (physicsComponent.mass + otherPhysicsComponent.mass);
                GLfloat v2nAfter = (v2n * (otherPhysicsComponent.mass - physicsComponent.mass) + 2.0f * physicsComponent.mass * v1n) / (physicsComponent.mass + otherPhysicsComponent.mass);

                GLfloat v1tAfter = v1t;
                GLfloat v2tAfter = v2t;

                velocities[ID] += v1nAfter * normalDirection + v1tAfter * tangentDirection;
                velocities[otherID] += v2nAfter * normalDirection + v2tAfter * tangentDirection;

                hasCollided[ID] = true;
                hasCollided[otherID] = true;
            }
        }        
    }
    
    for (GLuint ID = 0; ID < physicsComponents.size(); ID++)
    {       
        if (hasCollided[ID])
        {
            PhysicsComponent & physicsComponent = physicsComponents[ID];
            physicsComponent.velocity = velocities[ID];
        }
    }

    return;
}