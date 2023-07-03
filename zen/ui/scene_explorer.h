#ifndef GUI_IMGUI_SCENE_EXPLORER_H_
#define GUI_IMGUI_SCENE_EXPLORER_H_

#include <string>

#include "src/gui/imgui/window.h"
#include "src/gui/imgui/gui_store.h"
#include "src/utils/dependency_helper.h"
#include "src/core/scene/scene_manager.h"

namespace kuro {

namespace gui {

using SceneManager = core::SceneManager;

class SceneExplorer : public Window {
 public:
  explicit SceneExplorer(const std::string &name);

  void Render();

  REGISTER_DEPENDENCY(SceneManager, scene_manager_)
  REGISTER_DEPENDENCY(GuiStore, gui_store_)

 protected:
  bool TreeNode(std::shared_ptr<core::SceneNode> scene_node,
                ImGuiTreeNodeFlags flags = 0);

  void RenderNodes(std::shared_ptr<core::SceneNode> scene_node);
  const ImGuiTreeNodeFlags base_flags_ =
      ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
};

}  // namespace gui
}  // namespace kuro

#endif  // GUI_IMGUI_SCENE_EXPLORER_H_
