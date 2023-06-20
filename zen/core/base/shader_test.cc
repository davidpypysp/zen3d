#include <gtest/gtest.h>

#include "zen/core/base/shader.h"

namespace zen {

TEST(ShaderTest, BasicAssertions) {
  Shader shader("mesh.vert", "mesh_flat.frag");
}

} //  namespace zen
