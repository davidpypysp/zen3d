#include <gtest/gtest.h>

#include "zen/core/renderer/gl_render_api.h"
#include "zen/core/renderer/rendering_pipeline.h"

namespace zen {

TEST(RenderingPipelineTest, BasicAssertions) {
  auto render_api = std::make_shared<OpenGLAPI>();
  RenderingPipeline rendering_pipeline(render_api);
}

} //  namespace zen