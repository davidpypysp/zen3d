#pragma once

#include "zen/core/renderer/material.h"

namespace zen {

struct MeshFlatMaterial : public Material {
  MeshFlatMaterial();

  void PrepareRender(std::shared_ptr<RenderAPI> render_api,
                     std::shared_ptr<Camera> camera,
                     const math::vec3 &camera_position,
                     const math::vec3 &position) override;
};

} // namespace zen
