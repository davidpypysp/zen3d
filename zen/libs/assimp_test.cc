#include <iostream>

// assimp dependencies
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

extern "C" int main(int argc, char **argv) {
  std::cout << "something!!!" << std::endl;
  Assimp::Importer importer;

  return 0;
}