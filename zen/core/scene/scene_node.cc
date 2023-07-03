#include "zen/core/scene/scene_node.h"

namespace zen {

SceneNode::SceneNode(const std::string &name) : name_(name) {}

void SceneNode::AddChild(std::shared_ptr<SceneNode> scene_node) {
  children_.push_back(scene_node);
  scene_node->parent_ = shared_from_this();
}

} // namespace zen
