#include "config.hpp"
#include "controller/app.hpp"

App *app = new App();

int main (int argc, char *argv[]) {
  app->set_up_opengl();
  app->make_systems();

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  std::string scenePath = "scene_1.txt";
  AppCalculationMode mode = AppCalculationMode::CPU_ONLY;
  for (int i = 1; i < argc; i+=2)
  {
    char *arg = argv[i];
    if (arg == std::string("--file"))
    {
      scenePath = argv[i+1];
      continue;
    }
    if (arg == std::string("--mode"))
    {
      std::string modeStr = argv[i+1];
      if (modeStr == "CPU_ONLY")
        mode = AppCalculationMode::CPU_ONLY;
      else if (modeStr == "GPU_CPUCONTROLLER")
        mode = AppCalculationMode::GPU_CPUCONTROLLER;
      else if (modeStr == "GPU_ONLY")
        mode = AppCalculationMode::GPU_ONLY;
      else
      {
        std::cerr << "Unknown mode: " << modeStr << ". Using default CPU_ONLY mode." << std::endl;
        mode = AppCalculationMode::CPU_ONLY;
      }
      continue;
    }
  }

  app->run(scenePath, mode);

  delete app;

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  return 0;
}