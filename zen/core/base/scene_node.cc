#include "zen/core/base/scene_node.h"

namespace zen {

SceneNode::SceneNode(const std::string &name) : name_(name) {}

SceneNode::SceneNode(const std::string &name, const math::vec3 &position,
                     const math::vec3 &eular_rotation, const math::vec3 &scale)
    : name_(name), transform_(position, eular_rotation, scale) {}

void SceneNode::AddChild(const NodeHandle child_handle) {
  children_handles_.push_back(child_handle);
}

void SceneNode::SetParent(const NodeHandle parent_handle) {
  parent_handle_ = parent_handle;
}

math::vec3 &SceneNode::WorldPosition() { return transform_.WorldPosition(); }

void SceneNode::SetWorldPosition(const math::vec3 &position) {
  transform_.SetWorldPosition(position);
}

} // namespace zen
