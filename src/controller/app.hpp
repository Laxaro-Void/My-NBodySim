#pragma once
#include "../config.hpp"

#include "../components/camera_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"

#include "../systems/camera_system.hpp"
#include "../systems/motion_system.hpp"
#include "../systems/render_system.hpp"

#include "../view/shader.hpp"

class App {
public:
  App();
  ~App();

  void run();
  unsigned int make_entity();
  RenderComponent make_sphere_mesh(
    GLfloat R, 
    GLint sectorCount, 
    GLint stackCount, 
    unsigned int shader);

  void set_up_opengl();
  void make_systems();

  // Controler
  int Width = 720;
  int Height = 1080;

  // Components
  unsigned int cameraID;
  std::unordered_map<unsigned int, RenderComponent> renderComponents;
  std::unordered_map<unsigned int, CameraComponent> cameraComponents;
  std::unordered_map<unsigned int, TransformComponent> transformComponents;
  std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;

  std::vector<unsigned int> Shaders;
  
private:
  void set_up_glfw();

  unsigned int entity_count = 0;
  GLFWwindow* window;


  // Systems
  RenderSystem *renderSystem;
  CameraSystem *cameraSystem;
  MotionSystem *motionSystem;
};

extern App* app;
