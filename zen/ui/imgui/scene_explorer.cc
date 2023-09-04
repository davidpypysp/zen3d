#include "zen/ui/imgui/scene_explorer.h"
#include "zen/core/base/logging.h"

namespace zen {

SceneExplorer::SceneExplorer(const std::string& name) : Window(name) {}

bool SceneExplorer::RenderEntity(GuiStore& gui_store, EntityHandle& entity,
                                 ImGuiTreeNodeFlags flags) {
  auto& [scene, selected_entity] = gui_store;
  auto node_flags = base_flags_ | flags;
  if (selected_entity != kNullEntity && entity == selected_entity) {
    node_flags |= ImGuiTreeNodeFlags_Selected;
  }

  std::string title;
  auto* metadata = scene.try_get<EntityMetadata>(entity);
  if (metadata) {
    title = metadata->name;
  } else {
    title = "entity_id:" + EntityToStr(entity);
  }

  bool node_open = ImGui::TreeNodeEx(&entity, node_flags, "%s", title.c_str());
  if (ImGui::IsItemClicked()) {
    gui_store.selected_entity = entity;
    LOG(Info) << "Entity: " << title << " is clicked";
  }
  return node_open;
}

void SceneExplorer::Render(GuiStore& gui_store) {
  gui_store.scene.each([&](auto entity) {
    RenderEntity(gui_store, entity,
                 ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
  });
}

} // namespace zen
