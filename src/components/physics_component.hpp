#pragma once

struct __attribute__((packed)) PhysicsComponent {
    cl_float4 velocity = {0.0f, 0.0f, 0.0f, 0.0f};
    cl_float4 acceleration = {0.0f, 0.0f, 0.0f, 0.0f};
    cl_float mass;
    cl_float radius;
    cl_float pad1;
    cl_float pad2;
};