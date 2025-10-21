#include "config.hpp"
#include "controller/app.hpp"

App *app = new App();

int main (int argc, char *argv[]) {
  app->set_up_opengl();
  IMGUI_CHECKVERSION();

  app->run();

  

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return 0;
}