#include "config.hpp"
#include "controller/app.hpp"

App *app = new App();

int main (int argc, char *argv[]) {
  app->set_up_opengl();
  app->make_systems();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  app->run();

  delete app;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return 0;
}