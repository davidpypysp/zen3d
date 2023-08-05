#include "zen/core/renderer/renderer.h"
#include "zen/core/base/logging.h"

// TODO: abstract this
#include "zen/core/graphic_api/opengl_api.h"

namespace zen {

Renderer::Renderer() : rendering_pipeline_(std::make_shared<OpenGLAPI>()) {}

Renderer::~Renderer() {}

void Renderer::Init(std::shared_ptr<Scene> scene) {
  LOG(Info) << "Init Renderer";
  rendering_pipeline_.InitNode(scene->root_node());
}

void Renderer::Render(std::shared_ptr<Scene> scene,
                      std::shared_ptr<Camera> camera) {
  rendering_pipeline_.DrawNodes(scene->root_node(), camera);
}

} // namespace zen
