#include "zen/core/utils/wasm_wrapper.h"

#include "zen/core/renderer/rendering_pipeline.h"

#include "zen/core/graphic_api/opengl_api.h"

#include "zen/core/renderer/geometry_builder.h"
#include "zen/core/renderer/material_builder.h"

namespace zen {

class TestBody {
public:
  TestBody() {

    GeometryBuilder geometry_builder;
    MaterialBuilder material_builder;

    auto entity = scene.create();
    scene.emplace<Transform>(entity, math::vec3(0, 0, -5));
    Material material = material_builder.BuildSimpleMaterial();
    Geometry geometry = geometry_builder.BuildCubeGeometry();
    scene.emplace<Mesh>(entity, "mesh", geometry, material);

    camera_entity = scene.create();
    scene.emplace<Transform>(camera_entity, math::vec3(0, 0, 0));
    scene.emplace<Camera>(camera_entity, math::vec3(0, 0, 0));

    pipeline_ =
        std::make_shared<RenderingPipeline>(std::make_shared<OpenGLAPI>());
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

extern "C" int main(int argc, char** argv) {
  zen::TestBody test_body;
  zen::WasmWrapper wasm_manager(
      std::bind(&zen::TestBody::InitFunc, &test_body),
      std::bind(&zen::TestBody::RenderFunc, &test_body));
  zen::WasmSpin(wasm_manager);

  wasm_manager.Terminate();
  return 0;
}
