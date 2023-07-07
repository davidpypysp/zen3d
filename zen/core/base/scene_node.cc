#include "zen/core/base/scene_node.h"

namespace zen {

SceneNode::SceneNode(const std::string &name) : name_(name) {}

SceneNode::SceneNode(const std::string &name, const math::vec3 &position,
                     const math::vec3 &eular_rotation, const math::vec3 &scale)
    : transform_(position, eular_rotation, scale) {}

void SceneNode::AddChild(std::shared_ptr<SceneNode> scene_node) {
  children_.push_back(scene_node);
  scene_node->parent_ = shared_from_this();
}

math::vec3 &SceneNode::WorldPosition() { return transform_.WorldPosition(); }

void SceneNode::SetWorldPosition(const math::vec3 &position) {
  transform_.SetWorldPosition(position);
}

} // namespace zen
