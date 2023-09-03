#pragma once

#include "zen/core/base/scene.h"

namespace zen {

struct GuiStore {
  GuiStore(Scene& scene) : scene(scene) {}
  Scene& scene;
  Entity* selected_entity = nullptr;
};

} // namespace zen
