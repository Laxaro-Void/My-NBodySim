#include "src/controller/app.hpp"

App app = App();

App::App() {
  set_up_glfw();
}

App::~App() {
  

  glfwTerminate();
}

unsigned int App::make_sphere_mesh(float R, int sectorCount, int stackCount) {
  return 0;
}

void App::set_up_glfw() {
  if (!glfwInit())
  {
    std::cout << "Failed to initialize GLFW" << std::endl;
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  // Stable GLFW the version of OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  // Stable GLFW using the CORE profile
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // GLFW Window is Resizable = 1
  glfwWindowHint(GLFW_RESIZABLE, 1);

  window = glfwCreateWindow(Width, Height, "Project", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to open GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(window);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
  app.Width = width;
  app.Height = height;
};

void App::set_up_opengl() {
  if (!gladLoadGL())
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Specify the viewport of OpenGl in the Window
  glViewport(0, 0, Width, Height);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Enable 3D
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
}