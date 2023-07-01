#include "zen/core/renderer/mesh_flat_material.h"

namespace zen {

MeshFlatMaterial::MeshFlatMaterial() {
  shader_program = std::make_shared<ShaderProgram>(
      "mesh_flat_shader", "data/mesh.vert", "data/mesh_flat.frag");
}

void MeshFlatMaterial::render(std::shared_ptr<RenderAPI> render_api) {}

} //  namespace zen