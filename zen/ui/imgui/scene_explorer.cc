#include "zen/ui/imgui/scene_explorer.h"
#include "zen/core/base/logging.h"

namespace zen {

SceneExplorer::SceneExplorer(const std::string& name) : Window(name) {}

bool SceneExplorer::RenderEntity(Entity& entity,
                                 std::shared_ptr<GuiStore> gui_store,
                                 ImGuiTreeNodeFlags flags) {
  auto node_flags = base_flags_ | flags;
  if (entity.id() == gui_store->selected_entity->id()) {
    node_flags |= ImGuiTreeNodeFlags_Selected;
  }

  bool node_open =
      ImGui::TreeNodeEx(&entity, node_flags, "%s", entity.name().c_str());
  if (ImGui::IsItemClicked()) {
    gui_store->selected_entity = &entity;
    LOG(Info) << "Entity" << entity.name() << " clicked";
  }
  return node_open;
}

void SceneExplorer::Render(std::shared_ptr<GuiStore> gui_store) {
  for (auto& [id, entity] : gui_store->scene.entity_map()) {
    RenderEntity(entity, gui_store, base_flags_);
  }
}

} // namespace zen
