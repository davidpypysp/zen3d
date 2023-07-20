#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "zen/core/base/transform.h"

namespace zen {

class SceneNode : public std::enable_shared_from_this<SceneNode> {
public:
  SceneNode(const std::string &name);

  SceneNode(const std::string &name, const math::vec3 &position,
            const math::vec3 &eular_rotaion = math::vec3(0.0, 0.0, 0.0),
            const math::vec3 &scale = math::vec3(1.0, 1.0, 1.0));

  const std::string &name() const { return name_; }

  const std::vector<std::shared_ptr<SceneNode>> &children() const {
    return children_;
  }

  void AddChild(std::shared_ptr<SceneNode> node);

  math::vec3 &WorldPosition();

  void SetWorldPosition(const math::vec3 &position);

  Transform &transform() { return transform_; }

  bool is_renderable() { return is_renderable_; }

protected:
  std::string name_;
  Transform transform_;

  std::vector<std::shared_ptr<SceneNode>> children_;
  std::shared_ptr<SceneNode> parent_;

  bool is_renderable_ = false;
};

} // namespace zen
