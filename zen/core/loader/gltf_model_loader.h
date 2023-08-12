#pragma once

#include "tiny_gltf.h"

#include "zen/core/base/scene_node.h"
#include "zen/core/renderer/mesh.h"

namespace zen {

class GLTFModelLoader {
public:
  GLTFModelLoader();

  std::shared_ptr<SceneNode> LoadModel(const std::string &path);

  std::shared_ptr<SceneNode> ProcessNode(tinygltf::Model &model,
                                         tinygltf::Node &node);

  std::shared_ptr<SceneNode> ProcessMesh(tinygltf::Model &model,
                                         tinygltf::Mesh &mesh);

  std::shared_ptr<Mesh> ProcessMeshPrimitive(tinygltf::Model &model,
                                             tinygltf::Primitive &primitive);

protected:
  tinygltf::TinyGLTF loader_;
};

} // namespace zen