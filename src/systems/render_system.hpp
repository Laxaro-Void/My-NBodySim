#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"

class RenderSystem
{
public:
    RenderSystem(unsigned int shader, GLFWwindow *window);

    void update(
        std::unordered_map<unsigned int, TransformComponent> &transformComponents,
        std::unordered_map<unsigned int, RenderComponent> &renderComponents
    );

    void bindVAO(unsigned int ID);
    void bindVBO(unsigned int ID);
    void bindEBO(unsigned int ID);

    void linkAttributeVAO(unsigned int VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void *offset);

    void unbindVAO(unsigned int ID);
    void unbindVBO(unsigned int ID);
    void unbindEBO(unsigned int ID);

    void deleteVAO(unsigned int ID);
    void deleteVBO(unsigned int ID);
    void deleteEBO(unsigned int ID);

private:
    unsigned int modelLocation;
    GLFWwindow *window;
};

extern RenderSystem *render;