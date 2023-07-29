#include "zen/core/renderer/mesh_flat_material.h"

#include <iostream>

namespace zen {

MeshFlatMaterial::MeshFlatMaterial() {
  constexpr auto mesh_vert_shader = "zen/core/shader/mesh.vert";
  constexpr auto mesh_frag_shader = "zen/core/shader/mesh_flat.frag";
  shader_program = std::make_shared<ShaderProgram>(
      "mesh_flat_shader", mesh_vert_shader, mesh_frag_shader);
}

void MeshFlatMaterial::PrepareRender(std::shared_ptr<GraphicAPI> graphic_api,
                                     std::shared_ptr<Camera> camera,
                                     const math::mat4 &world_transform) {
  graphic_api->SetShaderMat4Param(shader_program, "model", world_transform);
  constexpr float kRatio = 3600.0 / 1800.0;
  graphic_api->SetShaderMat4Param(shader_program, "projection",
                                  camera->GetPerspectiveMatrix(kRatio));
  graphic_api->SetShaderMat4Param(shader_program, "view",
                                  camera->GetViewMatrix());
}

} //  namespace zen