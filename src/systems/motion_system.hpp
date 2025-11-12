#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"

class MotionSystem {
    public:
    
    void update(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt);

    void updateGravity(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt);
};