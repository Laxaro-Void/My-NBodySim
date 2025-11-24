#include "config.hpp"
#include "controller/app.hpp"

App *app = new App();

int main (int argc, char *argv[]) {
  app->set_up_opengl();
  app->make_systems();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  std::string scenePath = "scene_1.txt";
  for (int i = 1; i < argc; i+=2)
  {
    char *arg = argv[i];
    if (arg == std::string("--file"))
    {
      scenePath = argv[i+1];
    }
  }
  

  app->run(scenePath);

  delete app;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return 0;
}