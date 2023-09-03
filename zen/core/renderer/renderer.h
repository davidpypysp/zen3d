#pragma once

#include "zen/core/renderer/rendering_pipeline.h"

namespace zen {

class Renderer {
public:
  Renderer();

  ~Renderer();

  /**
   * Call after the scene is loaded.
   */
  void Init(Scene& scene);

  void Render(Scene& scene, EntityHandle& camera_entity);

  /**
   * Util function to grab the graphic api from the rendering pipeline.
   */
  std::shared_ptr<GraphicAPI> GetGraphicAPI() {
    return rendering_pipeline_.graphic_api();
  }

protected:
  RenderingPipeline rendering_pipeline_;
};

} // namespace zen
