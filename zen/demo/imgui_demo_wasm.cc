#include "zen/core/utils/wasm_wrapper.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/ui/imgui/gui.h"

#include "zen/core/renderer/cube_geometry.h"
#include "zen/core/renderer/mesh.h"
#include "zen/core/renderer/mesh_flat_material.h"
#include "zen/core/renderer/simple_material.h"
#include "zen/core/renderer/triangle_geometry.h"

namespace zen {

class ImguiDemo : public WasmWrapper {
public:
  ImguiDemo() {
    renderer = std::make_shared<Renderer>();
    scene = std::make_shared<Scene>();
    gui = std::make_shared<Gui>();
  }

  void Setup() override {
    auto material = std::make_shared<MeshFlatMaterial>();
    auto geometry = std::make_shared<CubeGeometry>();
    auto mesh = std::make_shared<Mesh>("simpe_mesh", geometry, material);
    mesh->SetWorldPosition(math::vec3(0, 0, -5));
    scene->AddNode(mesh);

    camera = std::make_shared<Camera>(math::vec3(0.0, 0.0, 0.0));
    scene->AddNode(camera);
    renderer->Init(scene);

    auto gui_store = std::make_shared<GuiStore>();
    gui_store->scene = scene;
    gui->Init(gui_store, params_.window);
  }

  void Render() override {
    renderer->Render(scene, camera);
    gui->Draw();
  }

  std::shared_ptr<Gui> gui;
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Renderer> renderer;
  std::shared_ptr<Scene> scene;
};

} // namespace zen

extern "C" int main(int argc, char **argv) {
  zen::ImguiDemo demo;

  zen::WasmSpin(demo);

  demo.Terminate();
  return 0;
}
