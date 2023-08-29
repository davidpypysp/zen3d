#include "zen/core/base/scene_node.h"

namespace zen {

SceneNode::SceneNode(const std::string &name, entt::entity entity)
    : name_(name), entity_(entity) {}

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
