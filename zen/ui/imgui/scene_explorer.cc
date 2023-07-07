#include "zen/ui/imgui/scene_explorer.h"

namespace zen {

SceneExplorer::SceneExplorer(const std::string &name) : Window(name) {}

bool SceneExplorer::TreeNode(std::shared_ptr<SceneNode> scene_node,
                             std::shared_ptr<GuiStore> gui_store,
                             ImGuiTreeNodeFlags flags) {
  auto node_flags = base_flags_ | flags;
  if (scene_node == gui_store->selected_scene_node) {
    node_flags |= ImGuiTreeNodeFlags_Selected;
  }
  // const std::string name = scene_node->name();
  bool node_open = ImGui::TreeNodeEx(scene_node.get(), node_flags, "abcd");
  if (ImGui::IsItemClicked()) {
    gui_store->selected_scene_node = scene_node;
    std::cout << "node " << scene_node->name() << " clicked" << std::endl;
  }
  return node_open;
}

void SceneExplorer::RenderNodes(std::shared_ptr<SceneNode> scene_node,
                                std::shared_ptr<GuiStore> gui_store) {
  if (scene_node->children().size() == 0) {
    TreeNode(scene_node, gui_store,
             ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);
    return;
  }

  bool node_open = TreeNode(scene_node, gui_store);
  if (node_open) {
    for (auto child_node : scene_node->children()) {
      RenderNodes(child_node, gui_store);
    }
    ImGui::TreePop();
  }
}

void SceneExplorer::Render(std::shared_ptr<GuiStore> gui_store) {
  RenderNodes(gui_store->scene->root_node(), gui_store);
}

} // namespace zen
