#pragma once
#include "../config.hpp"

struct __attribute__((packed)) TransformComponent {
    cl_float4 position;
    cl_float4 eulers;
    cl_float4 scale;
};