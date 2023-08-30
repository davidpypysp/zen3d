#pragma once

#include <vector>

#include "zen/core/base/entity.h"
#include "zen/core/base/resource_manager.h"

namespace zen {

class SceneGraph {
public:
  SceneGraph();

  Entity& CreateEntity();

  SceneRegistry& registry() { return scene_context_.registry; }

  template <typename... Components>
  inline auto View() {
    return scene_context_.registry.view<Components...>();
  }

private:
  SceneContext scene_context_;

  std::unordered_map<uint32_t, Entity> entity_map_;
};

} // namespace zen
