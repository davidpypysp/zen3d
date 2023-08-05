#pragma once

#include <memory>
#include <string>

// assimp dependencies
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "zen/core/base/scene_node.h"
#include "zen/core/loader/texture_loader.h"
#include "zen/core/renderer/mesh.h"

namespace zen {

class ModelLoader {
public:
  ModelLoader();

  std::shared_ptr<SceneNode> LoadModel(const std::string &path,
                                       std::shared_ptr<GraphicAPI> graphic_api);

protected:
  std::shared_ptr<SceneNode>
  ProcessNode(aiNode *ai_node, const aiScene *ai_scene,
              const std::string &directory,
              std::shared_ptr<GraphicAPI> graphic_api);

  std::shared_ptr<Mesh> ProcessMesh(aiMesh *ai_mesh, const aiScene *ai_scene,
                                    const std::string &directory,
                                    std::shared_ptr<GraphicAPI> graphic_api);

  std::vector<std::shared_ptr<Texture>>
  LoadMaterialTextures(aiMaterial *ai_mat, const std::string &directory,
                       const aiTextureType &ai_texture_type,
                       const TextureType &texture_type,
                       std::shared_ptr<GraphicAPI> graphic_api);

  Assimp::Importer importer_;
  TextureLoader texture_loader_;
};

} // namespace zen
