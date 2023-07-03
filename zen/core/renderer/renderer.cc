#include "zen/core/renderer/renderer.h"

namespace zen {

Renderer::Renderer() { rendering_pipeline_.Setup(); }

Renderer::~Renderer() {}

void Renderer::Render(std::shared_ptr<Scene> scene,
                      std::shared_ptr<CameraNode> camera_node) {
  rendering_pipeline_->DrawFrame(scene_manager_->root_node(), camera_node);
}

} //  namespace zen
