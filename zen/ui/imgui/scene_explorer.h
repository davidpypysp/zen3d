#pragma once

#include <string>

#include "zen/ui/imgui/window.h"

namespace zen {

class SceneExplorer : public Window {
public:
  explicit SceneExplorer(const std::string& name);

  void Render(std::shared_ptr<GuiStore> gui_store) override;

protected:
  bool RenderEntity(Entity& entity, std::shared_ptr<GuiStore> gui_store,
                    ImGuiTreeNodeFlags flags = 0);

  const ImGuiTreeNodeFlags base_flags_ =
      ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen;
};

} // namespace zen
