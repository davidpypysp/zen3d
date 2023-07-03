#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "zen/core/scene/transform.h"

namespace zen {

class SceneNode : public std::enable_shared_from_this<SceneNode> {
public:
  SceneNode(const std::string &name);

  std::string &name() { return name_; }

  const std::vector<std::shared_ptr<SceneNode>> &children() const {
    return children_;
  }

  void AddChild(std::shared_ptr<SceneNode> node);

protected:
  std::string name_;

  std::vector<std::shared_ptr<SceneNode>> children_;
  std::shared_ptr<SceneNode> parent_;
};

} // namespace zen
