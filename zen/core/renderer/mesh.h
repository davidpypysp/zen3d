#pragma once

#include "zen/core/renderer/geometry.h"
#include "zen/core/renderer/material.h"

namespace zen {

class Mesh : public SceneNode {
public:
  Mesh(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material);

  std::shared_ptr<Geometry> geometry() { return geometry_; }

  std::shared_ptr<Material> material() { return material_; }

protected:
  std::shared_ptr<Geometry> geometry_;

  std::shared_ptr<Material> material_;
};

} // namespace zen
