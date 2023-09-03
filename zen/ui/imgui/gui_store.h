#pragma once

#include "zen/core/base/scene.h"

namespace zen {

struct GuiStore {
  Scene& scene;
  Entity* selected_entity = nullptr;
};

} // namespace zen
