#include "zen/core/base/scene.h"

namespace zen {

Scene::Scene() {}

Entity& Scene::CreateEntity() {
  Entity entity(scene_context_);
  entity_map_.insert({entity.Id(), std::move(entity)});
  return entity_map_.at(entity.Id());
}

} // namespace zen