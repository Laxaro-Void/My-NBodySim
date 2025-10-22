#pragma once
#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/transform_component.hpp"

class CameraSystem {
public:

    CameraSystem(std::vector<unsigned int>* shader, GLFWwindow* window);
    
    bool update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        unsigned int cameraID, std::unordered_map<unsigned int, CameraComponent>& cameraComponent, float dt);
    
private:
    std::vector<unsigned int> *Shaders;
    glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    GLFWwindow* window;
};