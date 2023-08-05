#include "zen/core/renderer/simple_material.h"

namespace zen {

SimpleMaterial::SimpleMaterial() {}

void SimpleMaterial::Setup(std::shared_ptr<GraphicAPI> graphic_api) {
  constexpr auto mesh_vert_shader = "zen/core/shader/simple.vert";
  constexpr auto mesh_frag_shader = "zen/core/shader/mesh_flat.frag";
  shader_program =
      graphic_api->CreateShaderProgram(mesh_vert_shader, mesh_frag_shader);
}

} //  namespace zen