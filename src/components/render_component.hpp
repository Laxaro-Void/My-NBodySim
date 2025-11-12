#pragma once
#include "../config.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texUV;
};

enum class RenderType {
    STATIC,
    DYNAMIC,
    INSTANCED
};

struct RenderComponent {
    std::vector<Vertex> vertex;
    std::vector<GLuint> indexs;
    // std::vector<Texture> textures;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    
    unsigned int shader;
    
    RenderType renderType;
    unsigned int instanceSize;
    unsigned int instanceBuffer;
};
