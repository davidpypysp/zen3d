#include <gtest/gtest.h>

#include "zen/core/math/math.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  zen::math::vec3 p(1, 2, 3);
  // Expect equality.
  EXPECT_EQ(p.x, 1.0);
}