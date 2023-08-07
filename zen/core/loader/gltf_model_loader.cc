// tiny gltf define should be in .cc file
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "zen/core/loader/gltf_model_loader.h"

#include "zen/core/base/logging.h"
#include "zen/core/renderer/mesh_basic_material.h"

namespace zen {

GLTFModelLoader::GLTFModelLoader() {}

std::shared_ptr<SceneNode>
GLTFModelLoader::LoadModel(const std::string &path,
                           std::shared_ptr<GraphicAPI> graphic_api) {
  tinygltf::Model model;
  std::string err;
  std::string warn;

  bool ret = loader_.LoadASCIIFromFile(&model, &err, &warn, path);
  if (!warn.empty()) {
    printf("Warn: %s\n", warn.c_str());
  }

  if (!err.empty()) {
    printf("Err: %s\n", err.c_str());
  }

  if (!ret) {
    printf("Failed to parse glTF\n");
  }

  const tinygltf::Scene &scene = model.scenes[model.defaultScene];
  std::shared_ptr<SceneNode> root_node =
      std::make_shared<SceneNode>(scene.name);
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    auto &node = model.nodes[scene.nodes[i]];
    auto scene_node = ProcessNode(model, node, graphic_api);
    root_node->AddChild(scene_node);
  }
  return root_node;
}

std::shared_ptr<SceneNode>
GLTFModelLoader::ProcessNode(tinygltf::Model &model, tinygltf::Node &node,
                             std::shared_ptr<GraphicAPI> graphic_api) {
  auto scene_node = std::make_shared<SceneNode>(node.name);
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    auto &mesh = model.meshes[node.mesh];
    auto mesh_node = ProcessMesh(model, mesh, graphic_api);
    scene_node->AddChild(mesh_node);
  }
  for (size_t i = 0; i < node.children.size(); i++) {
    auto child_node =
        ProcessNode(model, model.nodes[node.children[i]], graphic_api);
    scene_node->AddChild(child_node);
  }
  return scene_node;
}

std::shared_ptr<Mesh>
GLTFModelLoader::ProcessMeshPrimitive(tinygltf::Model &model,
                                      tinygltf::Primitive &primitive,
                                      std::shared_ptr<GraphicAPI> graphic_api) {
  // indices
  std::vector<unsigned int> indices;
  {
    const tinygltf::Accessor &indicies_accessor =
        model.accessors[primitive.indices];
    const tinygltf::BufferView &bufferView =
        model.bufferViews[indicies_accessor.bufferView];
    // cast to float type read only. Use accessor and bufview byte offsets to
    // determine where position data
    // is located in the buffer.
    const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
    // bufferView byteoffset + accessor byteoffset tells you where the actual
    // position data is within the buffer. From there you should already know
    // how the data needs to be interpreted.
    const unsigned int *indices_array = reinterpret_cast<const unsigned int *>(
        &buffer.data[bufferView.byteOffset + indicies_accessor.byteOffset]);
    // From here, you choose what you wish to do with this position data. In
    // this case, we  will display it out.
    for (size_t i = 0; i < indicies_accessor.count; ++i) {
      indices.push_back(indices_array[i]);
    }
  }

  std::vector<Vertex> vertices(indices.size());
  {
    constexpr auto kPositionAttribute = "POSITION";
    const tinygltf::Accessor &position_accessor =
        model.accessors[primitive.attributes[kPositionAttribute]];
    const tinygltf::BufferView &bufferView =
        model.bufferViews[position_accessor.bufferView];
    const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
    const float *position_array = reinterpret_cast<const float *>(
        &buffer.data[bufferView.byteOffset + position_accessor.byteOffset]);
    for (size_t i = 0; i < position_accessor.count; ++i) {
      auto &position = vertices[i].position;
      position.x = position_array[i * 3 + 0];
      position.y = position_array[i * 3 + 1];
      position.z = position_array[i * 3 + 2];
    }
  }

  {
    constexpr auto kNormalAttribute = "NORMAL";
    const tinygltf::Accessor &normal_accessor =
        model.accessors[primitive.attributes[kNormalAttribute]];
    const tinygltf::BufferView &bufferView =
        model.bufferViews[normal_accessor.bufferView];
    const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
    const float *normal_array = reinterpret_cast<const float *>(
        &buffer.data[bufferView.byteOffset + normal_accessor.byteOffset]);
    for (size_t i = 0; i < normal_accessor.count; ++i) {
      auto &normal = vertices[i].normal;
      normal.x = normal_array[i * 3 + 0];
      normal.y = normal_array[i * 3 + 1];
      normal.z = normal_array[i * 3 + 2];
    }
  }

  {
    constexpr auto kTextureCoordinateAttribute = "TEXCOORD_0";
    const tinygltf::Accessor &tex_coord_accessor =
        model.accessors[primitive.attributes[kTextureCoordinateAttribute]];
    const tinygltf::BufferView &bufferView =
        model.bufferViews[tex_coord_accessor.bufferView];
    // cast to float type read only. Use accessor and bufview byte offsets to
    // determine where position data
    // is located in the buffer.
    const tinygltf::Buffer &buffer = model.buffers[bufferView.buffer];
    // bufferView byteoffset + accessor byteoffset tells you where the actual
    // position data is within the buffer. From there you should already know
    // how the data needs to be interpreted.
    const int *texture_coords_array = reinterpret_cast<const int *>(
        &buffer.data[bufferView.byteOffset + tex_coord_accessor.byteOffset]);
    // From here, you choose what you wish to do with this position data. In
    // this case, we  will display it out.
    for (size_t i = 0; i < tex_coord_accessor.count; ++i) {
      auto &tex_coords = vertices[i].tex_coords;
      tex_coords.x = texture_coords_array[i * 2 + 0];
      tex_coords.y = texture_coords_array[i * 2 + 1];
    }
  }
  auto geometry = std::make_shared<Geometry>(vertices, indices);

  //   const auto &material = model.materials[primitive.material];
  auto mesh_basic_material = std::make_shared<MeshBasicMaterial>();
  return std::make_shared<Mesh>("primitive", geometry, mesh_basic_material);
}

std::shared_ptr<SceneNode>
GLTFModelLoader::ProcessMesh(tinygltf::Model &model, tinygltf::Mesh &mesh,
                             std::shared_ptr<GraphicAPI> graphic_api) {
  auto scene_node = std::make_shared<SceneNode>(mesh.name);
  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    auto primitive_mesh_node =
        ProcessMeshPrimitive(model, mesh.primitives[i], graphic_api);
    scene_node->AddChild(primitive_mesh_node);
  }
  return scene_node;
}

} // namespace zen