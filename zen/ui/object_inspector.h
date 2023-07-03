#ifndef GUI_IMGUI_OBJECT_INSPECTOR_H_
#define GUI_IMGUI_OBJECT_INSPECTOR_H_

#include "src/gui/imgui/window.h"
#include "src/gui/imgui/gui_store.h"
#include "src/utils/dependency_helper.h"

namespace kuro {

namespace gui {

class ObjectInspector : public Window {
 public:
  explicit ObjectInspector(const std::string &name);

  void Render();

  REGISTER_DEPENDENCY(GuiStore, gui_store_)
};

}  // namespace gui

}  // namespace kuro

#endif  // GUI_IMGUI_OBJECT_INSPECTOR_H_
