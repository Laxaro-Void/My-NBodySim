#include "config.hpp"
#include "controller/app.hpp"

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

int main (int argc, char *argv[]) {

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
