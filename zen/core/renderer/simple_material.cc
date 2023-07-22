#include "zen/core/renderer/simple_material.h"

namespace zen {

SimpleMaterial::SimpleMaterial() {
  constexpr auto mesh_vert_shader = "zen/core/shader/simple.vert";
  constexpr auto mesh_frag_shader = "zen/core/shader/mesh_flat.frag";
  shader_program = std::make_shared<ShaderProgram>(
      "simple_material", mesh_vert_shader, mesh_frag_shader);
}

} //  namespace zen