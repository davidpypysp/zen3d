#include "zen/core/utils/window_wrapper.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/loader/model_loader.h"
#include "zen/ui/imgui/gui.h"

namespace zen {

class ModelLoaderDemo : public WindowWrapper {
public:
  ModelLoaderDemo() {
    renderer = std::make_shared<Renderer>();
    scene = std::make_shared<Scene>();
    gui = std::make_shared<Gui>();
    model_loader = std::make_shared<ModelLoader>();

    auto model_node =
        model_loader->LoadModel("data/backpack/backpack.obj",
                                renderer->rendering_pipeline_.graphic_api());
    scene->AddNode(model_node);

    camera = std::make_shared<Camera>(math::vec3(0.0, 0.0, 0.0));
    scene->AddNode(camera);
  }

  void Setup() override {
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
  std::shared_ptr<ModelLoader> model_loader;
};

} // namespace zen

int main(int argc, char **argv) {
  zen::ModelLoaderDemo demo;
  demo.Init();
  demo.Loop();
  demo.Terminate();
  return 0;
}
