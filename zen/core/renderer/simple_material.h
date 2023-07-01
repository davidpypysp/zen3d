#pragma once

#include "zen/core/renderer/material.h"

namespace zen {

// only render flat color in plain 2d display
struct SimpleMaterial : public Material {
  SimpleMaterial();
};

} // namespace zen
