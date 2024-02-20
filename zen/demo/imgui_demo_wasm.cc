#include "zen/core/utils/wasm_wrapper.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/ui/imgui/gui.h"

#include "zen/core/renderer/mesh.h"

#include "zen/core/renderer/geometry_builder.h"
#include "zen/core/renderer/material_builder.h"

namespace zen {

class ImguiDemo : public WasmWrapper {
public:
  ImguiDemo() {}

  void Setup() override {
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

    renderer.Init(scene);

    auto gui_store = std::make_shared<GuiStore>(scene);
    gui.Init(gui_store.get(), params_.window);
  }

  void Render() override {
    renderer.Render(scene, camera_entity);
    gui.Draw();
  }

  Gui gui;
  EntityHandle camera_entity;
  Renderer renderer;
  Scene scene;
};

} // namespace zen

extern "C" int main(int argc, char** argv) {
  zen::ImguiDemo demo;

  zen::WasmSpin(demo);

  demo.Terminate();
  return 0;
}
