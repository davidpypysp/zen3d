#include "zen/core/base/entity.h"
#include <iostream>

namespace zen {

Entity::Entity(SceneContext &scene_context)
    : scene_context_(scene_context),
      entity_handle_(scene_context.registry.create()) {}

} // namespace zen