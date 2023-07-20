#include "zen/core/renderer/wasm_wrapper.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/renderer/cube_geometry.h"
#include "zen/core/renderer/mesh.h"
#include "zen/core/renderer/mesh_flat_material.h"
#include "zen/core/renderer/simple_material.h"
#include "zen/core/renderer/triangle_geometry.h"

namespace zen {

struct TestBody {
public:
  TestBody() {
    renderer = std::make_shared<Renderer>();
    scene = std::make_shared<Scene>();

    auto material = std::make_shared<MeshFlatMaterial>();
    auto geometry = std::make_shared<CubeGeometry>();
    auto mesh = std::make_shared<Mesh>(geometry, material);
    mesh->SetWorldPosition(math::vec3(0, 0, -5));
    scene->AddNode(mesh);

    camera = std::make_shared<Camera>(math::vec3(0.0, 0.0, 0.0));
  }

  void InitFunc() { renderer->Init(scene); }

  void RenderFunc() { renderer->Render(scene, camera); }

protected:
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Renderer> renderer;
  std::shared_ptr<Scene> scene;
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
