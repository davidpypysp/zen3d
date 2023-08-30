#pragma once

#include "zen/core/renderer/geometry.h"
#include "zen/core/renderer/material.h"

namespace zen {

struct Mesh {
  std::string name;
  Geometry geometry;
  Material material;
};

} // namespace zen
