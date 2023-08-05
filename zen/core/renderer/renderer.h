#pragma once

#include "zen/core/base/scene.h"
#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/rendering_pipeline.h"

namespace zen {

class Renderer {
public:
  Renderer();

  ~Renderer();

  /**
   * Call after the scene is loaded.
   */
  void Init(std::shared_ptr<Scene> scene);

  void Render(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> camera);

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
