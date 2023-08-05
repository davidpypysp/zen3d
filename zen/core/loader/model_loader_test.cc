#include "zen/core/graphic_api/opengl_api.h"
#include "zen/core/loader/model_loader.h"

int main() {
  std::cout << "hello" << std::endl;
  zen::ModelLoader model_loader;
  auto graphic_api = std::make_shared<zen::OpenGLAPI>();
  auto scene_node =
      model_loader.LoadModel("data/backpack/backpack.obj", graphic_api);
  std::cout << "end" << std::endl;
  std::cout << "scene_node->name(): " << scene_node->name() << std::endl;
  return 0;
}