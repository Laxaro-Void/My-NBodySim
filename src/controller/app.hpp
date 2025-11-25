#pragma once
#include "../config.hpp"

#include "../components/camera_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"

#include "../systems/camera_system.hpp"
#include "../systems/motion_system.hpp"
#include "../systems/render_system.hpp"

#include "../view/shader.hpp"

enum class AppState {
    RUNNING,
    PAUSED,
    STOPPED
};

enum class AppCalculationMode {
    CPU_ONLY,
    GPU_CPUCONTROLLER,
    GPU_ONLY
};

class App {
public:
  App();
  ~App();

  void run(std::string scenePath);
  unsigned int make_entity();
  void delete_entity(unsigned int ID);
  RenderComponent make_sphere_mesh(
    GLfloat R, 
    GLint sectorCount, 
    GLint stackCount, 
    unsigned int shader
  );


  RenderComponent make_circle_mesh(
    GLfloat R,
    GLint sectorCount,
    unsigned int shader
  );

  RenderComponent make_bounding_box(
    GLfloat width,
    GLfloat height,
    GLfloat thickness,
    unsigned int shader
  );
  
  RenderComponent load_scene(const char* path, unsigned int shader);

  void set_up_opengl();
  void make_systems();

  // Controler
  int Width = 720;
  int Height = 1080;
  GLfloat dt = 16.67f / 1000.0f;
  GLfloat time = 0.0f;

  // Components
  unsigned int cameraID;
  std::unordered_map<unsigned int, RenderComponent> renderComponents;
  std::unordered_map<unsigned int, CameraComponent> cameraComponents;
  std::unordered_map<unsigned int, TransformComponent> transformComponents;
  std::unordered_map<unsigned int, PhysicsComponent> physicsComponents;

  unsigned int particlesInstanceID;
  std::vector<TransformComponent> particlesTranform;
  std::vector<PhysicsComponent> particlesPhysics;

  std::vector<unsigned int> Shaders;
  
private:
  void set_up_glfw();

  // State
  AppState state = AppState::RUNNING;
  AppCalculationMode calculationMode = AppCalculationMode::CPU_ONLY;

  // Entitys
  std::queue<unsigned int> freeEntity;
  unsigned int activeEntitys = 0;
  unsigned int leastEntity = 0;

  // Window
  GLFWwindow* window;

  // Inputs
  GLfloat input_dt = 16.67f / 1000.0f;
  struct Mouse
  {
    double x_pos, y_pos;
    double x_prev, y_prev;
    bool is_left_button_press, is_right_buttom_press;
    double scroll_x, scroll_y;

    Mouse()
    {
      x_pos = 0.0f;
      y_pos = 0.0f;
      x_prev = 0.0f;
      y_prev = 0.0f;
      is_left_button_press = false;
      is_right_buttom_press = false;
      scroll_x = 0.0f;
      scroll_y = 0.0f;
    };
    void updateMousePosition(GLFWwindow *window)
    {
      int width, height;
      glfwGetCursorPos(window, &x_pos, &y_pos);
      glfwGetFramebufferSize(window, &width, &height);
      y_pos = height - y_pos; // Invert Y axis Relative to OpenGL
      x_prev = x_pos;
      y_prev = y_pos;
    };
    void updateMouseButton(GLFWwindow *window)
    {
      is_left_button_press = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
      is_right_buttom_press = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
    };
    float getMouseScroll()
    {
      float val = scroll_y; 
      scroll_y = 0.0f;
      return val;
    }
  } mouse;

  // Systems
  RenderSystem *renderSystem;
  CameraSystem *cameraSystem;
  MotionSystem *motionSystem;

  // Kernels
};

extern App* app;
