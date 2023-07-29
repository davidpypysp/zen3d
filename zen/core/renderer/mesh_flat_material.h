#pragma once

#include "zen/core/renderer/material.h"

namespace zen {

struct MeshFlatMaterial : public Material {
  MeshFlatMaterial();

  void PrepareRender(std::shared_ptr<GraphicAPI> render_api,
                     std::shared_ptr<Camera> camera,
                     const math::mat4 &world_transform) override;
};

} // namespace zen
