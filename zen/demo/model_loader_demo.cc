#include "zen/core/utils/window_wrapper.h"

#include "zen/core/base/logging.h"
#include "zen/core/base/scene.h"
#include "zen/core/renderer/renderer.h"

#include "zen/core/renderer/cube_geometry.h"
#include "zen/core/renderer/mesh_flat_material.h"

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
  }

  void Setup() override {
    camera = std::make_shared<Camera>(math::vec3(0.0, 0.0, 2.0));
    scene->AddNode(camera);

    // add flat cube
    auto material = std::make_shared<MeshFlatMaterial>();
    auto geometry = std::make_shared<CubeGeometry>();
    auto mesh = std::make_shared<Mesh>("simple_cube", geometry, material);
    mesh->SetWorldPosition(math::vec3(0, 0, -5));
    scene->AddNode(mesh);

    // add backpack model
    auto model_node = model_loader->LoadModel("data/backpack/backpack.obj",
                                              renderer->GetGraphicAPI());
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
  std::shared_ptr<ModelLoader> model_loader;
};

} // namespace zen

int main(int argc, char **argv) {
  zen::ModelLoaderDemo demo;
  demo.Init();
  try {
    demo.Loop();

  } catch (const std::exception &e) {
    std::cout << "error: " << e.what() << std::endl;
  }
  demo.Terminate();
  return 0;
}
