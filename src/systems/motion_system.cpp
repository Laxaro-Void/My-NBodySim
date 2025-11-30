#include "motion_system.hpp"

void MotionSystem::updateGPU(
        cl::Buffer &transformComponents,
        cl::Buffer &physicsComponents,
        float dt, int N_particles, cl::Kernel &motionKernel, cl::CommandQueue &queue)
{
    cl::NDRange global( N_particles );
    motionKernel.setArg(0, transformComponents);
    motionKernel.setArg(1, physicsComponents);
    motionKernel.setArg(2, dt);
    
    queue.enqueueNDRangeKernel( motionKernel, cl::NullRange, global, local_threads );
}

void MotionSystem::updateCollisionGPU(
    cl::Buffer &transformComponents,
    cl::Buffer &physicsComponents,
    float dt, int N_particles, cl::Kernel &colisionKernel, cl::CommandQueue &queue)
{
    cl::NDRange global( N_particles );
    colisionKernel.setArg(0, transformComponents);
    colisionKernel.setArg(1, physicsComponents);
    colisionKernel.setArg(2, N_particles);
    
    queue.enqueueNDRangeKernel( colisionKernel, cl::NullRange, global, local_threads );
}

void MotionSystem::updateGravityGPU(
    cl::Buffer &transformComponents,
    cl::Buffer &physicsComponents,
    float dt, int N_particles, cl::Kernel &gravityKernel, cl::CommandQueue &queue)
    {
    cl::NDRange global( N_particles );
    gravityKernel.setArg(0, transformComponents);
    gravityKernel.setArg(1, physicsComponents);
    gravityKernel.setArg(2, G);
    gravityKernel.setArg(3, N_particles);
    
    queue.enqueueNDRangeKernel( gravityKernel, cl::NullRange, global, local_threads );
}

void MotionSystem::updateCPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt)
{
    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        TransformComponent trasnformComponent = transformComponents[ID];
        PhysicsComponent physicsComponent = physicsComponents[ID];

        transformComponents[ID].position.s[0] = trasnformComponent.position.s[0] + physicsComponent.velocity.s[0] * dt;
        transformComponents[ID].position.s[1] = trasnformComponent.position.s[1] + physicsComponent.velocity.s[1] * dt;
        transformComponents[ID].position.s[2] = trasnformComponent.position.s[2] + physicsComponent.velocity.s[2] * dt;
    }
    
    return;
}

void MotionSystem::updateGravityCPU(
    std::vector<TransformComponent> &transformComponents,
    std::vector<PhysicsComponent> &physicsComponents,
    float dt
)
{
    GLfloat epsilon = 0.1f * 0.1f; // Minimum distance to avoid singularity e^2

    std::vector<cl_float3> accelerations(physicsComponents.size(), {0.0f, 0.0f, 0.0f});

    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        TransformComponent trasnformComponent = transformComponents[ID];
        PhysicsComponent physicsComponent = physicsComponents[ID];

        cl_float3 totalAcceleration = {0.0f, 0.0f, 0.0f};
        for (GLuint otherID = 0; otherID < physicsComponents.size(); ++otherID)
        {
            TransformComponent otherTransformComponent = transformComponents[otherID];
            PhysicsComponent otherPhysicsComponent = physicsComponents[otherID];

            cl_float3 direction = otherTransformComponent.position - trasnformComponent.position;
            float distanceSquared = dot(direction, direction) + epsilon; // Avoid division by zero

            float distance = glm::sqrt(distanceSquared);
            cl_float3 forceDirection = direction / distance;
            // Gravitational force magnitude
            float forceMagnitude = (G * physicsComponent.mass * otherPhysicsComponent.mass) / distanceSquared;

            // Acceleration due to this force
            cl_float3 acceleration = (forceMagnitude / physicsComponent.mass) * forceDirection;

            totalAcceleration.s[0] += acceleration.s[0];
            totalAcceleration.s[1] += acceleration.s[1];
            totalAcceleration.s[2] += acceleration.s[2];
        }
        accelerations[ID] = totalAcceleration;
    }

    for (GLuint ID = 0; ID < physicsComponents.size(); ++ID)
    {
        physicsComponents[ID].velocity.s[0] += accelerations[ID].s[0] * dt;
        physicsComponents[ID].velocity.s[1] += accelerations[ID].s[1] * dt;
        physicsComponents[ID].velocity.s[2] += accelerations[ID].s[2] * dt;
    }
}

void MotionSystem::updateCollisionCPU(
        std::vector<TransformComponent> &transformComponents,
        std::vector<PhysicsComponent> &physicsComponents,
        float dt) 
{
    std::vector<cl_float3> velocities(physicsComponents.size(), {0.0f, 0.0f, 0.0f});
    std::vector<bool> hasCollided(physicsComponents.size(), false);

    for (size_t ID = 0; ID < physicsComponents.size(); ID++)
    {
        TransformComponent trasnformComponent = transformComponents[ID];
        PhysicsComponent physicsComponent = physicsComponents[ID];

        for (size_t otherID = ID + 1; otherID < physicsComponents.size(); otherID++)
        {
            TransformComponent otherTransformComponent = transformComponents[otherID];
            PhysicsComponent otherPhysicsComponent = physicsComponents[otherID];

            cl_float3 direction = otherTransformComponent.position - trasnformComponent.position;
            float distance = length(direction);

            if (distance < (physicsComponent.radius + otherPhysicsComponent.radius))
            {
                cl_float3 normalDirection = direction / distance;
                cl_float3 tangentDirection = {-normalDirection.s[1], normalDirection.s[0], 0.0f};

                float v1n = dot(physicsComponent.velocity, normalDirection);
                float v1t = dot(physicsComponent.velocity, tangentDirection);
                float v2n = dot(otherPhysicsComponent.velocity, normalDirection);
                float v2t = dot(otherPhysicsComponent.velocity, tangentDirection);

                float v1nAfter = (v1n * (physicsComponent.mass - otherPhysicsComponent.mass) + 2.0f * otherPhysicsComponent.mass * v2n) / (physicsComponent.mass + otherPhysicsComponent.mass);
                float v2nAfter = (v2n * (otherPhysicsComponent.mass - physicsComponent.mass) + 2.0f * physicsComponent.mass * v1n) / (physicsComponent.mass + otherPhysicsComponent.mass);

                float v1tAfter = v1t;
                float v2tAfter = v2t;

                velocities[ID].s[0] += v1nAfter * normalDirection.s[0] + v1tAfter * tangentDirection.s[0];
                velocities[ID].s[1] += v1nAfter * normalDirection.s[1] + v1tAfter * tangentDirection.s[1];
                velocities[ID].s[2] += v1nAfter * normalDirection.s[2] + v1tAfter * tangentDirection.s[2];

                velocities[otherID].s[0] += v2nAfter * normalDirection.s[0] + v2tAfter * tangentDirection.s[0];
                velocities[otherID].s[1] += v2nAfter * normalDirection.s[1] + v2tAfter * tangentDirection.s[1];
                velocities[otherID].s[2] += v2nAfter * normalDirection.s[2] + v2tAfter * tangentDirection.s[2];

                hasCollided[ID] = true;
                hasCollided[otherID] = true;
            }
        }        
    }
    
    for (GLuint ID = 0; ID < physicsComponents.size(); ID++)
    {       
        if (hasCollided[ID])
        {
            physicsComponents[ID].velocity = velocities[ID];
        }
    }

    return;
}