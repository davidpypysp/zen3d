#include "zen/core/base/logging.h"
#include "zen/core/base/scene.h"
#include "zen/core/renderer/geometry_builder.h"
#include "zen/core/renderer/material_builder.h"
#include "zen/core/renderer/renderer.h"
#include "zen/core/utils/window_wrapper.h"

#include "zen/ui/imgui/gui.h"

#include "zen/core/renderer/mesh.h"

namespace zen {

class ImguiDemo : public WindowWrapper {
public:
  ImguiDemo() : gui_store(scene) {
    GeometryBuilder geometry_builder;
    MaterialBuilder material_builder;

    auto entity = scene.AddEntity("mesh_entity");
    scene.emplace<Transform>(entity, math::vec3(0, 0, -5));
    Material material = material_builder.BuildSimpleMaterial();
    Geometry geometry = geometry_builder.BuildCubeGeometry();
    scene.emplace<Mesh>(entity, "mesh", geometry, material);

    camera_entity = scene.AddEntity("camera_entity");
    scene.emplace<Transform>(camera_entity, math::vec3(0, 0, 0));
    scene.emplace<Camera>(camera_entity, math::vec3(0, 0, 0));
  }

  void Setup() override {
    renderer.Init(scene);

    gui.Init(&gui_store, params_.window);
  }

  void Render() override {
    renderer.Render(scene, camera_entity);
    gui.Draw();
  }

  void Terminate() { glfwTerminate(); }

protected:
  Gui gui;
  GuiStore gui_store;

  Renderer renderer;

  Scene scene;
  EntityHandle camera_entity = kNullEntity;
};

} // namespace zen

int main(int argc, char** argv) {
  zen::ImguiDemo demo;

  demo.Init();
  demo.Loop();
  demo.Terminate();
  return 0;
}
