#pragma once

#include "zen/core/renderer/material.h"

namespace zen {

struct MeshFlatMaterial : public Material {
  MeshFlatMaterial();

  void Setup(std::shared_ptr<GraphicAPI> graphic_api) override;

  void PrepareRender(std::shared_ptr<GraphicAPI> graphic_api,
                     std::shared_ptr<Camera> camera,
                     const math::mat4 &world_transform) override;
};

} // namespace zen
