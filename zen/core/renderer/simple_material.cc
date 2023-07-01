#include "zen/core/renderer/simple_material.h"

namespace zen {

SimpleMaterial::SimpleMaterial() {
  shader_program = std::make_shared<ShaderProgram>(
      "simple_material", "data/simple.vert", "data/mesh_flat.frag");
}

void SimpleMaterial::render(std::shared_ptr<RenderAPI> render_api) {}

} //  namespace zen