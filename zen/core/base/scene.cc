#include "zen/core/base/scene.h"

namespace zen {

Scene::Scene() {}

Entity& Scene::CreateEntity() {
  Entity entity(scene_context_);
  entity_map_.insert({entity.id(), std::move(entity)});
  return entity_map_.at(entity.id());
}

} // namespace zen