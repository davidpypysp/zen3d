#pragma once

#include <memory>
#include <vector>

#include "zen/core/base/handle.h"
#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/renderer/vertex.h"

namespace zen {

// Geometry info for constructing rendering data
struct Geometry {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::shared_ptr<Handle> handle;

  Geometry() {}

  virtual ~Geometry() = default;

  Geometry(const std::vector<Vertex> &vertices,
           const std::vector<unsigned int> &indices)
      : vertices(vertices), indices(indices) {}

  virtual void Setup(std::shared_ptr<GraphicAPI> render_api) = 0;
};

} //  namespace zen
