#pragma once

#include <memory>
#include <string>
#include <vector>

#include "zen/core/base/resource_manager.h"
#include "zen/core/base/scene_node.h"

namespace zen {

class Scene {
public:
  Scene();

  SceneNode &root_node() { return *scene_node_manager_.Get(root_handle_); }

  SceneNode &camera_node() { return *scene_node_manager_.Get(camera_handle_); }

  SceneNode &CreateNode(const std::string &name,
                        const NodeHandle parent_handle = 0);

  void SetCameraNode(NodeHandle camera_handle);

protected:
  ResourceManager<SceneNode, NodeHandle> scene_node_manager_;

  NodeHandle root_handle_;
  NodeHandle camera_handle_;
};

} // namespace zen
