#pragma once

#include "src/core/renderer/rendering_pipeline.h"
#include "src/core/scene/scene_manager.h"

namespace zen {

class Renderer {
public:
  Renderer();

  ~Renderer();

  void Render();

  RenderingPipeline rendering_pipeline_;
};

} // namespace zen
