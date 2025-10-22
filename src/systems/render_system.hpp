#pragma once
#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"
#include "../view/shader.hpp"

class RenderSystem
{
public:
    RenderSystem(GLFWwindow *window);

    void update(
        std::unordered_map<unsigned int, TransformComponent> &transformComponents,
        std::unordered_map<unsigned int, RenderComponent> &renderComponents,
        std::vector<unsigned int> &Shaders
    );

    void uploadVertexData(RenderComponent &renderComponent);

    void bindVAO(unsigned int ID);
    void bindVBO(unsigned int ID);
    void bindEBO(unsigned int ID);

    void linkAttribute(
        unsigned int VBO, 
        GLuint layout, 
        GLuint numComponents, 
        GLenum type, 
        GLsizeiptr stride, 
        void *offset);

    void unbindVAO(unsigned int ID);
    void unbindVBO(unsigned int ID);
    void unbindEBO(unsigned int ID);

    void deleteVAO(unsigned int ID);
    void deleteVBO(unsigned int ID);
    void deleteEBO(unsigned int ID);

private:
    GLFWwindow *window;
};

extern RenderSystem *render;