#pragma once

#include "zen/core/base/scene.h"
#include "zen/core/base/scene_node.h"

namespace zen {

struct GuiStore {
  std::shared_ptr<SceneNode> selected_scene_node;

  std::shared_ptr<Scene> scene;
};

} // namespace zen
