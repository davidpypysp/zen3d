#pragma once

#include "zen/core/renderer/geometry.h"

namespace zen {

struct TriangleGeometry : public Geometry {
  TriangleGeometry() {
    positions = {math::vec3(0.5, 0.5, 0.0), math::vec3(0.5, -0.5, 0.0),
                 math::vec3(-0.5, -0.5, 0.0), math::vec3(-0.5, 0.5, 0.0)};
    // indices = {0, 1, 3, 1, 2, 3};
    indices = {0, 1, 3};
  }

  void Setup(std::shared_ptr<GraphicAPI> graphic_api) {
    this->handle = graphic_api->CreateGeometryInstanceWithPositions(
        this->positions, this->indices);
  }

  std::vector<math::vec3> positions;
  std::vector<unsigned int> indices;
};

} // namespace zen
