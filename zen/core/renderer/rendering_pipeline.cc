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

void RenderingPipeline::InitGeometry(Geometry &geometry) {
  geometry.Setup(render_api_);
}

void RenderingPipeline::InitShader(Material &material) {
  auto shader_program = material.shader_program;

  material.shader_program = render_api_->CreateShaderProgram(
      shader_program->vertex_shader_path.c_str(),
      shader_program->fragment_shader_path.c_str(),
      shader_program->geometry_shader_path.c_str());
}

void RenderingPipeline::SetTranslation(Material &material,
                                       const math::mat4 &model) {
  render_api_->SetShaderMat4Param(material.shader_program, "model", model);
}

void RenderingPipeline::PrepareDraw(Material &material, Camera &camera,
                                    const math::vec3 &camera_translation) {
  std::cout << "prepare draw" << std::endl;
  auto shader_program = material.shader_program;
  render_api_->EnableShaderProgram(shader_program);

  // // TODO: turn ratio to window height/width
  // constexpr float kRatio = 300.0 / 150.0;
  // const auto &perspective_matrix = camera.GetPerspectiveMatrix(kRatio);
  // render_api_->SetShaderMat4Param(shader_program, "projection",
  //                                 perspective_matrix);
  // const auto &view_matrix = camera.GetViewMatrix(camera_translation);
  // std::cout << "view_matrix: " << math::to_string(view_matrix) << std::endl;
  // render_api_->SetShaderMat4Param(shader_program, "view", view_matrix);
}

void RenderingPipeline::DrawMesh(Geometry &geometry, Material &material) {
  material.render(render_api_);
  render_api_->DrawMeshInstance(geometry.handle);
}

} //  namespace zen