#include "zen/core/base/scene_graph.h"

namespace zen {

SceneGraph::SceneGraph() {}

Entity &SceneGraph::CreateEntity() {
  Entity entity(scene_context_);
  entity_map_.insert({entity.Id(), std::move(entity)});
  return entity_map_.at(entity.Id());
}

} // namespace zen