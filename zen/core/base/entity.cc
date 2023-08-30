#include "zen/core/base/entity.h"

namespace zen {

Entity::Entity(SceneContext* scene_context) : scene_context_(scene_context) {
    const auto& entity = scene_context_->registry.create();
}

}