#pragma once

#include <memory>

#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/geometry.h"
#include "zen/core/renderer/material.h"
#include "zen/core/renderer/render_api.h"

namespace zen {

class RenderingPipeline {
public:
  RenderingPipeline();

  void Setup();

  void InitGeometry(Geometry &geometry);

  void InitShader(Material &material);

  void SetTranslation(Material &material, const math::mat4 &model);

  void PrepareDraw(Material &material, Camera &camera,
                   const math::vec3 &camera_translation);

  void DrawMesh(Geometry &geometry, Material &material);

protected:
  std::shared_ptr<RenderAPI> render_api_;
};

} //  namespace zen
