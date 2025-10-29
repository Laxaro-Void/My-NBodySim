#include "motion_system.hpp"

void MotionSystem::update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        std::unordered_map<unsigned int,PhysicsComponent> &physicsComponents,
        float dt)
{

    for (auto &&It : physicsComponents)
    {
        unsigned int ID = It.first;
        TransformComponent & trasnformComponent = transformComponents[ID];
        PhysicsComponent & physicsComponent = physicsComponents[ID];

        trasnformComponent.position += physicsComponent.velocity * dt;
    }
    
    return;
}

void MotionSystem::updateGravity(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    std::unordered_map<unsigned int,PhysicsComponent> &physicsComponents,
    float dt, std::vector<unsigned int> &entityIDs
)
{
    GLfloat g = -9.807; // u/s^2
    for (auto &&ID : entityIDs)
    {
        TransformComponent & trasnformComponent = transformComponents[ID];
        PhysicsComponent & physicsComponent = physicsComponents[ID];

        physicsComponent.velocity.y += g * dt;
    }
    
}