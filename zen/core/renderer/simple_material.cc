#include "zen/core/renderer/simple_material.h"

namespace zen {

SimpleMaterial::SimpleMaterial() {
  shader_program = std::make_shared<ShaderProgram>(
      "simple_material", "data/simple.vert", "data/mesh_flat.frag");
}

} //  namespace zen