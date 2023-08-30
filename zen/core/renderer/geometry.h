#pragma once

#include "zen/core/graphic_api/graphic_api.h"

namespace zen {

// Geometry info for constructing rendering data
struct Geometry {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::shared_ptr<GeometryHandle> handle;
};

} //  namespace zen
