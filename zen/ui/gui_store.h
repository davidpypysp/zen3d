#ifndef GUI_IMGUI_GUI_STORE_H_
#define GUI_IMGUI_GUI_STORE_H_

#include "src/core/scene/scene_node.h"
#include "src/utils/type_annotation.h"

namespace kuro {

namespace gui {

struct GuiStore {
  std::shared_ptr<core::SceneNode> selected_scene_node;
};

}  // namespace gui

REGISTER_TYPE_ANNOTATION(gui::GuiStore)

}  // namespace kuro

#endif