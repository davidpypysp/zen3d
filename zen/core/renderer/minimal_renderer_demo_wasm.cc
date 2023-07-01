#include "zen/core/renderer/wasm_api.h"

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
    material_ = std::make_shared<SimpleMaterial>();
    geometry_ = std::make_shared<TriangleGeometry>();

    camera_ = std::make_shared<Camera>();
  }

  void InitFunc() {
    std::cout << "init here yay111" << std::endl;
    pipeline_.InitGeometry(*geometry_);
    pipeline_.InitShader(*material_);
    std::cout << "init func debug 1" << std::endl;
  }

  void RenderFunc() {
    math::vec3 camera_position(3, 0, 0);
    std::cout << "before prepare draw" << std::endl;
    math::mat4 model(1.0);
    model = math::translate(model, math::vec3(0, 0, 0));
    std::cout << "model:" << math::to_string(model) << std::endl;
    pipeline_.PrepareDraw(*material_, *camera_, camera_position);
    pipeline_.SetTranslation(*material_, model);
    pipeline_.DrawMesh(*geometry_, *material_);
  }

protected:
  std::shared_ptr<Material> material_;
  std::shared_ptr<Geometry> geometry_;
  std::shared_ptr<Camera> camera_;

  RenderingPipeline pipeline_;
};

} // namespace zen

extern "C" int main(int argc, char **argv) {
  zen::TestBody test_body;
  zen::WasmManager wasm_manager(
      std::bind(&zen::TestBody::InitFunc, &test_body),
      std::bind(&zen::TestBody::RenderFunc, &test_body));
  zen::WasmSpin(wasm_manager);

  wasm_manager.Terminate();
  return 0;
}
