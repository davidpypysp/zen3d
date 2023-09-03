#include "zen/core/base/scene.h"

namespace zen {

std::string EntityToStr(EntityHandle entity) {
  return std::to_string(uint32_t(entity));
}

Scene::Scene() {}

EntityHandle Scene::AddEntity(const std::string& name) {
  EntityHandle entity = create();
  emplace<EntityMetadata>(entity, name);
  return entity;
}

} // namespace zen