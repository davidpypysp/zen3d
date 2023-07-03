#ifndef GUI_IMGUI_GUI_SYSTEM_H_
#define GUI_IMGUI_GUI_SYSTEM_H_

#include <iostream>
#include <memory>

#include <glad/glad.h>  // Initialize with gladLoadGL()
#include <GLFW/glfw3.h>

#include "src/utils/type_annotation.h"
#include "src/utils/dependency_helper.h"
#include "src/gui/imgui/gui_manager.h"
#include "src/gui/imgui/context.h"
#include "src/core/engine.h"

namespace kuro {

namespace gui {

class GuiSystem {
 public:
  GuiSystem();

  ~GuiSystem();

  int Run();

  REGISTER_DEPENDENCY(Engine, engine_)
  REGISTER_DEPENDENCY(GuiManager, gui_manager_)

 protected:
  int Init();

  void Loop();

  void Cleanup();

  std::shared_ptr<Context> context_;

  GLFWwindow* gl_window_;
};

}  // namespace gui

REGISTER_TYPE_ANNOTATION(gui::GuiSystem)

}  // namespace kuro

#endif