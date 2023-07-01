#include "zen/core/renderer/mesh_flat_material.h"

namespace zen {

MeshFlatMaterial::MeshFlatMaterial() {
  shader_program = std::make_shared<ShaderProgram>(
      "mesh_flat_shader", "data/mesh.vert", "data/mesh_flat.frag");
}

void MeshFlatMaterial::PrepareRender(std::shared_ptr<RenderAPI> render_api,
                                     std::shared_ptr<Camera> camera,
                                     const math::vec3 &camera_position,
                                     const math::vec3 &position) {
  constexpr float kRatio = 3600.0 / 1800.0;
  render_api->SetShaderMat4Param(shader_program, "projection",
                                 camera->GetPerspectiveMatrix(kRatio));
  render_api->SetShaderMat4Param(shader_program, "view",
                                 camera->GetViewMatrix(camera_position));
}

} //  namespace zen