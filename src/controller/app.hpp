#pragma once
#include "../config.hpp"

class App {
public:
  App();
  ~App();

  void run();
  unsigned int make_entity();
  unsigned int make_sphere_mesh(float R, int sectorCount, int stackCount);

  void set_up_opengl();
  void make_systems();

  // Controler
  int Width = 720;
  int Height = 1080;

  // Components
  unsigned int cameraID;

private:
  void set_up_glfw();

  unsigned int entity_count = 0;
  GLFWwindow* window;

  std::vector<unsigned int> VAOs;
  std::vector<unsigned int> VBOs;
  // std::vector<unsigned int> textures;

  unsigned int shader;

  // Systems
};

extern App app;
