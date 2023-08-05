#include <gtest/gtest.h>

#include "zen/core/renderer/mesh.h"
#include "zen/core/renderer/simple_material.h"
#include "zen/core/renderer/triangle_geometry.h"

namespace zen {

TEST(MeshTest, BasicAssertions) {
  auto geometry = std::make_shared<TriangleGeometry>();
  auto material = std::make_shared<SimpleMaterial>();

  Mesh mesh("test_mesh", geometry, material);
}

} //  namespace zen
