#pragma once
#include "../config.hpp"

struct alignas(16) TransformComponent {
    cl_float3 position;
    cl_float3 eulers;
    cl_float3 scale;
};