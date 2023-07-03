#pragma once

#include "zen/core/base/scene.h"
#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/rendering_pipeline.h"

namespace zen {

class Renderer {
public:
  Renderer();

  ~Renderer();

  void Init(std::shared_ptr<Scene> scene);

  void Render(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> camera);

  RenderingPipeline rendering_pipeline_;
};

} // namespace zen
