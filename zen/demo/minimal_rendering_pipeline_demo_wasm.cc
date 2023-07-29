#include "zen/core/renderer/wasm_wrapper.h"

#include "zen/core/renderer/rendering_pipeline.h"

#include "zen/core/renderer/gl_render_api.h"

#include "zen/core/renderer/cube_geometry.h"
#include "zen/core/renderer/mesh_flat_material.h"
#include "zen/core/renderer/simple_material.h"
#include "zen/core/renderer/triangle_geometry.h"

namespace zen {

class TestBody {
public:
  TestBody() {
    pipeline_ =
        std::make_shared<RenderingPipeline>(std::make_shared<OpenGLAPI>());
    bool use_cube = true;
    if (use_cube) {
      material_ = std::make_shared<MeshFlatMaterial>();
      geometry_ = std::make_shared<CubeGeometry>();
    } else {
      // use triangle and render in 2d without camera
      material_ = std::make_shared<SimpleMaterial>();
      geometry_ = std::make_shared<TriangleGeometry>();
    }

    camera_ = std::make_shared<Camera>(math::vec3(0.0, 0.0, 0.0));
  }

  void InitFunc() {
    pipeline_->InitGeometry(geometry_);
    pipeline_->InitMaterial(material_);
  }

  void RenderFunc() {
    math::vec3 object_position(0, 0, -5);
    math::mat4 world_transform =
        math::translate(math::mat4(1.0), object_position);
    pipeline_->PrepareDraw(material_, camera_, world_transform);
    pipeline_->DrawMesh(geometry_, material_);
  }

protected:
  std::shared_ptr<Material> material_;
  std::shared_ptr<Geometry> geometry_;
  std::shared_ptr<Camera> camera_;

  std::shared_ptr<RenderingPipeline> pipeline_;
};

} // namespace zen

extern "C" int main(int argc, char **argv) {
  zen::TestBody test_body;
  zen::WasmWrapper wasm_manager(
      std::bind(&zen::TestBody::InitFunc, &test_body),
      std::bind(&zen::TestBody::RenderFunc, &test_body));
  zen::WasmSpin(wasm_manager);

  wasm_manager.Terminate();
  return 0;
}
