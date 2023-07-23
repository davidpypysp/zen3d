#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

int main() {
  Assimp::Importer importer;
  importer.ReadFile("test", aiProcess_Triangulate);
  std::cout << " importer test" << std::endl;
}
