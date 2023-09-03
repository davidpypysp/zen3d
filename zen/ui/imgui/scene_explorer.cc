#include "zen/ui/imgui/scene_explorer.h"
#include "zen/core/base/logging.h"

namespace zen {

SceneExplorer::SceneExplorer(const std::string& name) : Window(name) {}

bool SceneExplorer::RenderEntity(std::shared_ptr<GuiStore> gui_store,
                                 EntityHandle& entity,
                                 ImGuiTreeNodeFlags flags) {
  auto node_flags = base_flags_ | flags;
  if (gui_store->selected_entity != kNullEntity &&
      entity == gui_store->selected_entity) {
    node_flags |= ImGuiTreeNodeFlags_Selected;
  }

  auto entity_id = EntityToStr(entity);
  bool node_open =
      ImGui::TreeNodeEx(&entity, node_flags, "%s", entity_id.c_str());
  if (ImGui::IsItemClicked()) {
    gui_store->selected_entity = entity;
    LOG(Info) << "Entity: " << entity_id << " is clicked";
  }
  return node_open;
}

void SceneExplorer::Render(std::shared_ptr<GuiStore> gui_store) {
  gui_store->scene.each([&](auto entity) {
    RenderEntity(gui_store, entity,
                 ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
  });
}

} // namespace zen
