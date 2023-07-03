#ifndef GUI_IMGUI_GUI_MANAGER_H_
#define GUI_IMGUI_GUI_MANAGER_H_

#include <string>
#include <memory>

#include "src/utils/type_annotation.h"
#include "src/utils/dependency_helper.h"
#include "src/gui/imgui/gui_store.h"
#include "src/gui/imgui/scene_explorer.h"
#include "src/gui/imgui/object_inspector.h"
#include "src/core/engine.h"

namespace kuro {

namespace gui {

using SceneManager = core::SceneManager;
using Engine = core::Engine;

class GuiManager {
 public:
  GuiManager();

  void Init();

  void Draw();

  REGISTER_DEPENDENCY(GuiStore, gui_store_)
  REGISTER_DEPENDENCY(Engine, engine_)

 protected:
  void InitWindows();

  template <class T>
  std::shared_ptr<T> AddWindow(const std::string& name) {
    std::shared_ptr<Window> window = std::make_shared<T>(name);
    windows_.push_back(window);
    return std::static_pointer_cast<T>(window);
  }

  std::vector<std::shared_ptr<Window>> windows_;
};

}  // namespace gui

REGISTER_TYPE_ANNOTATION(gui::GuiManager)

}  // namespace kuro

#endif  // GUI_IMGUI_GUI_H_
