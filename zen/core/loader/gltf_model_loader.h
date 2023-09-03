#pragma once

#include "tiny_gltf.h"

#include "zen/core/base/scene.h"
#include "zen/core/renderer/mesh.h"

namespace zen {

class GLTFModelLoader {
public:
  GLTFModelLoader();

  void LoadModel(const std::string& path, Scene& scene);

  void ProcessNode(tinygltf::Model& model, tinygltf::Node& node, Scene& scene,
                   EntityHandle parent);

  void ProcessMesh(tinygltf::Model& model, tinygltf::Mesh& mesh, Scene& scene,
                   EntityHandle entity);

  Geometry ProcessMeshPrimitive(tinygltf::Model& model,
                                tinygltf::Primitive& primitive);

  template <typename T>
  const T* getRawPrimitiveData(tinygltf::Model& model,
                               const int& accessor_index) {
    tinygltf::Accessor& accessor = model.accessors[accessor_index];
    tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
    // cast to float type read only. Use accessor and bufview byte offsets to
    // determine where position data
    // is located in the buffer.
    tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
    // bufferView byteoffset + accessor byteoffset tells you where the actual
    // position data is within the buffer. From there you should already know
    // how the data needs to be interpreted.
    const auto* data_array = reinterpret_cast<const T*>(
        &buffer.data[bufferView.byteOffset + accessor.byteOffset]);
    return data_array;
  }

protected:
  tinygltf::TinyGLTF loader_;
};

} // namespace zen