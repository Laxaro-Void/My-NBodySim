#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"

class MotionSystem {
    public:
    void updateGPU(
        cl::Buffer &transformComponents,
        cl::Buffer &physicsComponents,
        float dt, int N_particles, cl::Kernel &motionKernel, cl::CommandQueue &queue);
        
    void updateCollisionGPU(
        cl::Buffer &transformComponents,
        cl::Buffer &physicsComponents,
        float dt, int N_particles, cl::Kernel &colisionKernel, cl::CommandQueue &queue);
        
    void updateGravityGPU(
        cl::Buffer &transformComponents,
        cl::Buffer &physicsComponents,
        float dt, int N_particles, cl::Kernel &gravityKernel, cl::CommandQueue &queue);
    
    void updateCPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt);
    
    void updateGravityCPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt);

    
    void updateCollisionCPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt);

    GLfloat G;
};