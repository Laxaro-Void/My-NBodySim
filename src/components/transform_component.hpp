#pragma once
#include "../config.hpp"

struct __attribute__((packed)) TransformComponent {
    cl_float3 position;
    cl_float3 eulers;
    cl_float3 scale;
    cl_float2 shearX;
    cl_float2 shearY;
    cl_float2 shearZ;
};