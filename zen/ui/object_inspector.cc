#include "src/gui/imgui/object_inspector.h"

namespace kuro {

namespace gui {

ObjectInspector::ObjectInspector(const std::string &name) : Window(name) {}

void ObjectInspector::Render() {
  auto scene_node = gui_store_->selected_scene_node;
  if (!scene_node) {
    return;
  }

  ImGui::InputText("Name", const_cast<char *>(scene_node->name().c_str()),
                   scene_node->name().size());
  // ImGui::LabelText("Type", scene_node->Type());
  ImGui::SliderFloat3("Translation", scene_node->LocalTranslationPtr(), -10.0,
                      10.0);
  ImGui::SliderFloat3("Rotation", scene_node->LocalRotationPtr(), -10.0, 10.0);
  ImGui::SliderFloat3("Scale", scene_node->LocalScalePtr(), 0.1, 2.0);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
              1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}

}  // namespace gui

}  // namespace kuro