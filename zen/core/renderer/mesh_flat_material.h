#pragma once

#include "zen/core/renderer/material.h"

namespace zen {

struct MeshFlatMaterial : public Material {
  MeshFlatMaterial();

  void render(std::shared_ptr<RenderAPI> render_api) override;
};

} // namespace zen
