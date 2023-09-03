#include "zen/ui/imgui/object_inspector.h"
#include "zen/core/base/logging.h"
#include "zen/core/base/transform.h"

namespace zen {

ObjectInspector::ObjectInspector(const std::string& name) : Window(name) {}

void ObjectInspector::Render(std::shared_ptr<GuiStore> gui_store) {
  auto* selected_entity = gui_store->selected_entity;
  if (!selected_entity) {
    return;
  }

  auto& transform = selected_entity->GetComponent<Transform>();

  ImGui::InputText("Name", const_cast<char*>(selected_entity->name().c_str()),
                   selected_entity->name().size());
  // ImGui::LabelText("Type", scene_node->Type().c_str());
  ImGui::SliderFloat3("Translation", &transform.WorldPosition()[0], -100.0,
                      100.0);
  // ImGui::SliderFloat3("Rotation", scene_node->LocalRotationPtr(),
  // -10.0, 10.0); ImGui::SliderFloat3("Scale", scene_node->LocalScalePtr(),
  // 0.1, 2.0);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace zen