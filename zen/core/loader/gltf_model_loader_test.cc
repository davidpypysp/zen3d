#include "zen/core/loader/gltf_model_loader.h"

int main() {
  zen::GLTFModelLoader loader;
  auto scene_node = loader.LoadModel("data/duck_gltf/Duck.gltf");
  std::cout << "scene_node name: " << scene_node->children().size()
            << std::endl;
  return 0;
}