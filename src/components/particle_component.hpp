#pragma once
#include "../config.hpp"

struct ParticleComponent
{
    GLfloat position[3];
    GLfloat velocity[3];
    GLfloat radius;
    GLfloat mass;
};
