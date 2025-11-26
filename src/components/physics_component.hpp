#pragma once

struct __attribute__((packed)) PhysicsComponent {
    cl_float3 velocity = {0.0f, 0.0f, 0.0f};
    cl_float3 acceleration = {0.0f, 0.0f, 0.0f};
    cl_float mass;
    cl_float radius;
};