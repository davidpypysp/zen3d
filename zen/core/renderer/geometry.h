#pragma once

#include "zen/core/graphic_api/geometry_handle.h"
#include "zen/core/graphic_api/vertex.h"

namespace zen {

// Geometry info for constructing rendering data
struct Geometry {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  GeometryHandle handle;
};

} //  namespace zen
