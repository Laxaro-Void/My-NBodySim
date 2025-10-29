#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/transform_component.hpp"

#include "../view/shader.hpp"

class CameraSystem {
public:

    CameraSystem(GLFWwindow* window);
    
    bool update3D(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponent, 
        std::vector<unsigned int> &Shaders, float dt);

    bool update2D(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponents, 
        std::vector<unsigned int> &Shaders, float dt);
    
    void Inputs3D(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponent,
        float dt
    );

    void Inputs2D(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponent,
        float dt
    );

private:
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
};