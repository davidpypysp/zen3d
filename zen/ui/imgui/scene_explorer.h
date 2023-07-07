#pragma once

#include <string>

#include "zen/ui/imgui/window.h"

namespace zen {

class SceneExplorer : public Window {
public:
  explicit SceneExplorer(const std::string &name);

  void Render(std::shared_ptr<GuiStore> gui_store) override;

protected:
  bool TreeNode(std::shared_ptr<SceneNode> scene_node,
                std::shared_ptr<GuiStore> gui_store,
                ImGuiTreeNodeFlags flags = 0);

  void RenderNodes(std::shared_ptr<SceneNode> scene_node,
                   std::shared_ptr<GuiStore> gui_store);

  const ImGuiTreeNodeFlags base_flags_ =
      ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
};

} // namespace zen
