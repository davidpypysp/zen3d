#include "zen/core/renderer/rendering_pipeline.h"
#include "zen/core/base/logging.h"

// TODO: refactor initialization of this
#include "zen/core/renderer/mesh.h"

#include <iostream>
#include <memory>

namespace zen {

/**
 * @brief Construct a new Rendering Pipeline:: Rendering Pipeline object
 */
RenderingPipeline::RenderingPipeline(std::shared_ptr<GraphicAPI> graphic_api)
    : graphic_api_(graphic_api) {}

void RenderingPipeline::InitMeshes(SceneGraph& scene_graph) {
  auto view = scene_graph.View<Mesh>();
  for (auto [entity, mesh] : view.each()) {
    auto& geometry = mesh.geometry;
    geometry.handle = graphic_api_->CreateGeometryInstance(geometry.vertices,
                                                           geometry.indices);

    auto& material = mesh.material;
    material.shader_program = graphic_api_->CreateShaderProgram(
        material.vertex_shader_path, material.fragment_shader_path);
  }
}

void RenderingPipeline::RenderMeshes(SceneGraph& scene_graph) {
  Camera camera;
  Transform camera_transform;
  auto view = scene_graph.View<Mesh, Transform>();
  for (const auto& [entity, mesh, transform] : view.each()) {
    const auto& world_transform = transform.ModelMatrix();
    PrepareDraw(mesh.material, camera, world_transform, camera_transform);
    DrawMesh(mesh);
  }
}

void RenderingPipeline::PrepareDraw(const Material& material,
                                    const Camera& camera,
                                    const math::mat4& world_transform,
                                    Transform& camera_transform) {
  graphic_api_->EnableShaderProgram(material.shader_program);
  // material PrepareRender(graphic_api_, camera, world_transform);

  // flat mesh material draw
  graphic_api_->SetShaderMat4Param(material.shader_program, "model",
                                   world_transform);
  constexpr float kRatio = 3600.0 / 1800.0;
  graphic_api_->SetShaderMat4Param(material.shader_program, "projection",
                                   camera.GetPerspectiveMatrix(kRatio));
  const auto& camera_view_matrix =
      camera.GetViewMatrix(camera_transform.WorldPosition());
  graphic_api_->SetShaderMat4Param(material.shader_program, "view",
                                   camera_view_matrix);
}

void RenderingPipeline::DrawMesh(const Mesh& mesh) {
  graphic_api_->DrawMeshInstance(mesh.geometry.handle);
}

} //  namespace zen