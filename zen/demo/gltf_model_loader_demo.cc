#include "zen/core/utils/window_wrapper.h"

#include "zen/core/base/logging.h"
#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/loader/gltf_model_loader.h"
#include "zen/ui/imgui/gui.h"

namespace zen {

class GLTFModelLoaderDemo : public WindowWrapper {
public:
  GLTFModelLoaderDemo() : gui_store(scene) {}

  void Setup() override {
    camera_entity = scene.AddEntity("camera_entity");
    scene.emplace<Transform>(camera_entity, math::vec3(0, 0, 5));
    scene.emplace<Camera>(camera_entity);

    // add backpack model

    gltf_model_loader.LoadModel("data/cube_gltf/Cube.gltf", scene);

    // init scene
    renderer.Init(scene);
    gui.Init(&gui_store, params_.window);
  }

  void Render() override {
    renderer.Render(scene, camera_entity);
    gui.Draw();
  }

  Gui gui;
  GuiStore gui_store;
  Renderer renderer;

  EntityHandle camera_entity;
  Scene scene;

  GLTFModelLoader gltf_model_loader;
};

} // namespace zen

int main(int argc, char** argv) {
  zen::GLTFModelLoaderDemo demo;
  demo.Init();
  try {
    demo.Loop();

  } catch (const std::exception& e) {
    std::cout << "error: " << e.what() << std::endl;
  }
  demo.Terminate();
  return 0;
}
