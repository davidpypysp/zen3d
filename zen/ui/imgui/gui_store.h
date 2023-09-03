#pragma once

#include "zen/core/base/scene.h"

namespace zen {

struct GuiStore {
  GuiStore(Scene& scene) : scene(scene) {}
  Scene& scene;
  EntityHandle* selected_entity = nullptr;
};

} // namespace zen
