#include "zen/core/base/scene.h"

namespace zen {

std::string EntityToStr(EntityHandle entity) {
  return std::to_string(uint32_t(entity));
}

Scene::Scene() {}

} // namespace zen