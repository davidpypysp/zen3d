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

  void InitGeometry(std::shared_ptr<Geometry> geometry);

  void InitMaterial(std::shared_ptr<Material> material);

  void PrepareDraw(std::shared_ptr<Material> material,
                   std::shared_ptr<Camera> camera,
                   const math::vec3 &camera_position,
                   const math::mat4 &world_transform);

  void DrawMesh(Geometry &geometry, Material &material);

protected:
  std::shared_ptr<RenderAPI> render_api_;
};

} //  namespace zen
