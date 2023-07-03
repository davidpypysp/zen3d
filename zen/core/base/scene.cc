#include "zen/core/base/scene.h"

namespace zen {

Scene::Scene() { root_node_ = std::make_shared<SceneNode>("root"); }

void Scene::SetCameraNode(std::shared_ptr<SceneNode> camera_node) {
  camera_node_ = camera_node;
}

void Scene::AddNode(std::shared_ptr<SceneNode> node) {
  root_node_->AddChild(node);
}

} // namespace zen