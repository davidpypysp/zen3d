#include "zen/ui/imgui/object_inspector.h"
#include "zen/core/base/logging.h"

namespace zen {

ObjectInspector::ObjectInspector(const std::string &name) : Window(name) {}

void ObjectInspector::Render(std::shared_ptr<GuiStore> gui_store) {
  auto scene_node = gui_store->selected_scene_node;
  if (!scene_node) {
    return;
  }

  ImGui::InputText("Name", const_cast<char *>(scene_node->name().c_str()),
                   scene_node->name().size());
  ImGui::LabelText("Type", scene_node->Type().c_str());
  ImGui::SliderFloat3("Translation", &scene_node->WorldPosition()[0], -10.0,
                      10.0);
  // ImGui::SliderFloat3("Rotation", scene_node->LocalRotationPtr(),
  // -10.0, 10.0); ImGui::SliderFloat3("Scale", scene_node->LocalScalePtr(),
  // 0.1, 2.0);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

} // namespace zen