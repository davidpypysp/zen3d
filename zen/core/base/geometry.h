#pragma once

#include <memory>
#include <vector>

#include "zen/core/base/handle.h"
#include "zen/core/base/vertex.h"

namespace zen {

// Geometry info for constructing rendering data
struct Geometry {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::shared_ptr<Handle> handle;

  Geometry() {}

  Geometry(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices)
      : vertices(vertices), indices(indices) {}
};

} //  namespace zen
