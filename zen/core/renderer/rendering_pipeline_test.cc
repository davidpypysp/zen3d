#include <gtest/gtest.h>

#include "zen/core/graphic_api/opengl_api.h"
#include "zen/core/renderer/rendering_pipeline.h"

namespace zen {

TEST(RenderingPipelineTest, BasicAssertions) {
  auto graphic_api = std::make_shared<OpenGLAPI>();
  RenderingPipeline rendering_pipeline(graphic_api);
}

} //  namespace zen