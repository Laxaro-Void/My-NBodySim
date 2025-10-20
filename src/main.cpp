// Glad, GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Stdc++
#include <bits/stdc++.h>

// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow *window = nullptr;
int HEIGHT = 720;
int WIDTH = 1080;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
  WIDTH = width;
  HEIGHT = height;
}

void createWindow()
{
  /*
    Ceate a Basic GLFW-Window of a specific size
  */
  window = glfwCreateWindow(WIDTH, HEIGHT, "Project", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to open GLFW window" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Make the window into the current context
  glfwMakeContextCurrent(window);
}

void glfw_glad_Initial()
{
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

  createWindow();

  // Load GLAD to configures OpenGl
  if (!gladLoadGL())
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  // Specify the viewport of OpenGl in the Window
  glViewport(0, 0, WIDTH, HEIGHT);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Enable 3D
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);

  // Scrool CallBack
  // glfwSetScrollCallback(window, scrollCallback);
}

int main (int argc, char *argv[]) {
  glfw_glad_Initial();
  IMGUI_CHECKVERSION();

  while (!glfwWindowShouldClose(window))
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
