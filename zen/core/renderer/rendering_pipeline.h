#pragma once

#include <memory>

#include "src/core/renderer/render_api.h"
#include "src/core/renderer/shader_manager.h"
#include "zen/core/base/geometry.h"
#include "zen/core/base/material.h"

namespace zen {

class RenderingPipeline {
public:
  RenderingPipeline();

  void Setup();

  // // Render one frame by gpu (given all mesh, light...)
  // void DrawFrame(std::shared_ptr<SceneNode> root_node,
  //                std::shared_ptr<SceneNode> camera_node);

  // dependencies
  std::shared_ptr<RenderAPI> render_api_;
  std::shared_ptr<ShaderManager> shader_manager_;

protected:
  void PrepareDraw(const Camera &camera);

  void DrawMesh(const Geometry &geometry, const Material &material);
};

} //  namespace zen
