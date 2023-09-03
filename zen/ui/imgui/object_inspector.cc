#include "zen/ui/imgui/object_inspector.h"
#include "zen/core/base/logging.h"
#include "zen/core/base/transform.h"
#include "zen/ui/imgui/utils.h"

namespace zen {

ObjectInspector::ObjectInspector(const std::string& name) : Window(name) {}

void ObjectInspector::Render(GuiStore& gui_store) {
  auto& [scene, selected_entity] = gui_store;
  if (selected_entity == kNullEntity) {
    return;
  }

  const auto entity_id = EntityToStr(selected_entity);
  InputTextComponent("Id", entity_id);

  auto* metadata = scene.try_get<EntityMetadata>(selected_entity);
  if (metadata) {
    InputTextComponent("Name", metadata->name);
    // ImGui::LabelText("Type", scene_node->Type().c_str());
  }

  auto* transform = scene.try_get<Transform>(selected_entity);
  if (transform) {
    Vector3Component("Translation", transform->WorldPosition(), -100.0, 100.0);
    // ImGui::SliderFloat3("Rotation", scene_node->LocalRotationPtr(),
    // -10.0, 10.0); ImGui::SliderFloat3("Scale", scene_node->LocalScalePtr(),
    // 0.1, 2.0);
  }

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace zen