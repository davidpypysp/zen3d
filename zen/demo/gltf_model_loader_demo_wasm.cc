#include "zen/core/utils/wasm_wrapper.h"

#include "zen/core/base/logging.h"
#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/loader/gltf_model_loader.h"
#include "zen/ui/imgui/gui.h"

namespace zen {

class GLTFModelLoaderDemo : public WasmWrapper {
public:
  GLTFModelLoaderDemo() {
    renderer = std::make_shared<Renderer>();
    scene = std::make_shared<Scene>();
    gui = std::make_shared<Gui>();
    gltf_model_loader = std::make_shared<GLTFModelLoader>();
  }

  void Setup() override {
    camera = std::make_shared<Camera>(math::vec3(0.0, 0.0, 8.0));
    scene->AddNode(camera);

    // add backpack model
    auto model_node = gltf_model_loader->LoadModel("data/glb/ToyCar.glb");
    scene->AddNode(model_node);

    // init scene
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
  std::shared_ptr<GLTFModelLoader> gltf_model_loader;
};

} // namespace zen

int main(int argc, char **argv) {
  zen::GLTFModelLoaderDemo demo;

  zen::WasmSpin(demo);

  demo.Terminate();
  return 0;
}
