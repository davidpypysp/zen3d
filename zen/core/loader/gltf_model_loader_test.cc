#include "zen/core/loader/gltf_model_loader.h"
#include <iostream>

int main() {
  zen::GLTFModelLoader loader;
  zen::Scene scene;
  loader.LoadModel("data/duck_gltf/Duck.gltf", scene);
  std::cout << "Hello, World!" << std::endl;
  return 0;
}