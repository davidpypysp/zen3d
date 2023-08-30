#include "zen/core/utils/wasm_wrapper.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/renderer/geometry_builder.h"
#include "zen/core/renderer/material_builder.h"
#include "zen/core/renderer/mesh.h"

namespace zen {

struct MinimalRendererDemoWasm : public WasmWrapper {
public:
  MinimalRendererDemoWasm() {
    GeometryBuilder geometry_builder;
    MaterialBuilder material_builder;

    auto entity = scene.CreateEntity();
    entity.AddComponent<Transform>(math::vec3(0, 0, -5));
    Material material = material_builder.BuildSimpleMaterial();
    Geometry geometry = geometry_builder.BuildCubeGeometry();
    entity.AddComponent<Mesh>({"mesh", geometry, material});

    camera_entity = &scene.CreateEntity();
    camera_entity->AddComponent<Transform>(math::vec3(0, 0, 0));
    camera_entity->AddComponent<Camera>(math::vec3(0, 0, 0));
  }

  void Setup() { renderer.Init(scene); }

  void Render() { renderer.Render(scene, *camera_entity); }

protected:
  Entity* camera_entity;
  Renderer renderer;
  Scene scene;
};

} // namespace zen

extern "C" int main(int argc, char** argv) {
  zen::MinimalRendererDemoWasm demo;
  zen::WasmSpin(demo);
  demo.Terminate();

  return 0;
}
