#include "zen/core/renderer/renderer.h"
#include "zen/core/base/logging.h"

// TODO: abstract this
#include "zen/core/graphic_api/opengl_api.h"

namespace zen {

/**
 * TODO: This is a temporary solution. We should have a way to specify the
 * graphic api
 */
Renderer::Renderer() : rendering_pipeline_(std::make_shared<OpenGLAPI>()) {}

Renderer::~Renderer() {}

void Renderer::Init(Scene& scene) {
  LOG(Info) << "Init Renderer";
  rendering_pipeline_.InitMeshes(scene);
}

void Renderer::Render(Scene& scene, Entity& camera_entity) {
  rendering_pipeline_.RenderMeshes(scene);
}

} // namespace zen
