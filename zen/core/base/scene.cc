#include "zen/core/base/scene.h"

namespace zen {

Scene::Scene() {
  root_handle_ = scene_node_manager_.Create("root_node", registry_.create());
}

SceneNode &Scene::CreateNode(const std::string &name,
                             const NodeHandle parent_handle) {
  entt::entity entity = registry_.create();
  const auto handle = scene_node_manager_.Create(name, entity);
  auto *node = scene_node_manager_.Get(handle);
  if (parent_handle != 0) {
    auto *parent_node = scene_node_manager_.Get(parent_handle);
    parent_node->AddChild(handle);
    node->SetParent(parent_handle);
  }
  return *node;
}

void Scene::SetCameraNode(NodeHandle camera_handle) {
  camera_handle_ = camera_handle;
}

} // namespace zen
