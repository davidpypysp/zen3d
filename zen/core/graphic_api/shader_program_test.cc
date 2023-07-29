#include <gtest/gtest.h>

#include "zen/core/graphic_api/shader_program.h"

namespace zen {

TEST(ShaderProgramTest, BasicAssertions) {
  ShaderProgram shader_program("mesh.vert", "mesh_flat.frag");
}

} //  namespace zen
