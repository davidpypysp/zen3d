#pragma once

#include <memory>
#include <string>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "zen/ui/imgui/gui_store.h"
#include "zen/ui/imgui/object_inspector.h"
#include "zen/ui/imgui/scene_explorer.h"

namespace zen {

class Gui {
public:
  Gui();

  void Init(GuiStore* gui_store, GLFWwindow* window);

  void Draw();

protected:
  GuiStore* gui_store_;

  void InitImgui(GLFWwindow* window);

  void InitWindows();

  template <class T>
  std::shared_ptr<T> AddWindow(const std::string& name) {
    std::shared_ptr<Window> window = std::make_shared<T>(name);
    windows_.push_back(window);
    return std::static_pointer_cast<T>(window);
  }

  std::vector<std::shared_ptr<Window>> windows_;
};

} // namespace zen
