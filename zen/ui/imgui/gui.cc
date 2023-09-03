#include "zen/ui/imgui/gui.h"

#include <iostream>

namespace zen {

Gui::Gui() {}

void Gui::Init(GuiStore* gui_store, GLFWwindow* gl_window) {
  gui_store_ = gui_store;
  InitImgui(gl_window);
  InitWindows();
}

void Gui::Draw() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  for (auto window : windows_) {
    window->RenderFrame(*gui_store_);
  }

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Gui::InitImgui(GLFWwindow* gl_window) {
  // Setup Dear ImGui binding
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(gl_window, true);
  ImGui_ImplOpenGL3_Init();

  // Setup style
  ImGui::StyleColorsDark();

  ImGuiIO& io = ImGui::GetIO();

  // Load Fonts
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 23.0f);
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 18.0f);
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 26.0f);
  io.Fonts->AddFontFromFileTTF("data/xkcd-script.ttf", 32.0f);
  io.Fonts->AddFontDefault();
}

void Gui::InitWindows() {
  auto scene_explorer = AddWindow<SceneExplorer>("Scene Explorer");
  auto object_inspector = AddWindow<ObjectInspector>("Object Inspector");
}

} // namespace zen
