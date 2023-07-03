#pragma once

#include <memory>
#include <string>
#include <vector>

#include "zen/core/scene/scene_node.h"

namespace zen {

class Scene {
public:
  Scene();

  std::shared_ptr<SceneNode> root_node() { return root_node_; }

  std::shared_ptr<SceneNode> camera_node() { return camera_node_; }

  void SetCameraNode(std::shared_ptr<SceneNode> camera_node);

protected:
  std::shared_ptr<SceneNode> root_node_;
  std::shared_ptr<SceneNode> camera_node_;
};

} // namespace zen
