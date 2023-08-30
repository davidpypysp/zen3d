#pragma once

#include <entt/entt.hpp>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "zen/core/base/handle.h"
#include "zen/core/base/transform.h"

namespace zen {

typedef ResourceHandle NodeHandle;

class SceneNode {
public:
  SceneNode(entt::registry &registry);

  virtual ~SceneNode() = default;

  template <typename T> void AddComponent(T component) {
    registry_.emplace<T>(entity_, component);
  }

  void AddChild(const NodeHandle child_handle);

  void SetParent(const NodeHandle parent_handle);

  const std::string &name() const { return name_; }

  math::vec3 &WorldPosition();

  void SetWorldPosition(const math::vec3 &position);

  Transform &transform() { return transform_; }

  bool is_renderable() { return is_renderable_; }

protected:
  entt::registry &registry_;
  entt::entity entity_;

  std::string name_;
  Transform transform_;

  std::vector<NodeHandle> children_handles_;
  NodeHandle parent_handle_ = 0;

  bool is_renderable_ = false;
};

} // namespace zen
