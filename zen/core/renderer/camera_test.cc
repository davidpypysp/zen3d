#include <gtest/gtest.h>

#include "zen/core/renderer/camera.h"

namespace zen {

TEST(CameraCompTest, BasicAssertions) {
  Camera camera;

  EXPECT_EQ(camera.zoom(), 45.0);
}

} //  namespace zen
