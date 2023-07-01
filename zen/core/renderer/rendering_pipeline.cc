#include "zen/core/renderer/rendering_pipeline.h"

// TODO: refactor initialization of this
#include "zen/core/renderer/gl_render_api.h"

#include <iostream>
#include <memory>

namespace zen {

RenderingPipeline::RenderingPipeline() {
  render_api_ = std::make_shared<GLRenderAPI>();
}

void RenderingPipeline::Setup() {}

void RenderingPipeline::InitGeometry(std::shared_ptr<Geometry> geometry) {
  geometry->Setup(render_api_);
}

void RenderingPipeline::InitMaterial(std::shared_ptr<Material> material) {
  auto shader_program = material->shader_program;
  material->shader_program = render_api_->CreateShaderProgram(
      shader_program->vertex_shader_path.c_str(),
      shader_program->fragment_shader_path.c_str(),
      shader_program->geometry_shader_path.c_str());
}

void RenderingPipeline::PrepareDraw(std::shared_ptr<Material> material,
                                    std::shared_ptr<Camera> camera,
                                    const math::vec3 &camera_position,
                                    const math::mat4 &world_transform) {
  render_api_->EnableShaderProgram(material->shader_program);
  material->PrepareRender(render_api_, camera, camera_position,
                          world_transform);
}

void RenderingPipeline::DrawMesh(Geometry &geometry, Material &material) {
  render_api_->DrawMeshInstance(geometry.handle);
}

} //  namespace zen