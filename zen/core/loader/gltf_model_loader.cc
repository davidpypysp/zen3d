// tiny gltf define should be in .cc file
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "zen/core/loader/gltf_model_loader.h"

#include "zen/core/base/logging.h"
#include "zen/core/renderer/mesh_flat_material.h"

namespace zen {

GLTFModelLoader::GLTFModelLoader() {}

std::shared_ptr<SceneNode> GLTFModelLoader::LoadModel(const std::string &path) {
  tinygltf::Model model;
  std::string err;
  std::string warn;

  bool ret = false;
  if (path.find(".gltf") != std::string::npos) {
    ret = loader_.LoadASCIIFromFile(&model, &err, &warn, path);
  } else if (path.find(".glb") != std::string::npos) {
    ret = loader_.LoadBinaryFromFile(&model, &err, &warn, path);
  } else {
    LOG(Error) << "Unknown file format: " << path;
  }
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
      std::make_shared<SceneNode>("scene:" + scene.name);
  for (size_t i = 0; i < scene.nodes.size(); ++i) {
    auto &node = model.nodes[scene.nodes[i]];
    auto scene_node = ProcessNode(model, node);
    root_node->AddChild(scene_node);
  }
  return root_node;
}

std::shared_ptr<SceneNode> GLTFModelLoader::ProcessNode(tinygltf::Model &model,
                                                        tinygltf::Node &node) {
  auto scene_node = std::make_shared<SceneNode>(node.name);
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    auto &mesh = model.meshes[node.mesh];
    auto mesh_node = ProcessMesh(model, mesh);
    scene_node->AddChild(mesh_node);
  }
  for (size_t i = 0; i < node.children.size(); i++) {
    auto child_node = ProcessNode(model, model.nodes[node.children[i]]);
    scene_node->AddChild(child_node);
  }
  return scene_node;
}

std::shared_ptr<Mesh>
GLTFModelLoader::ProcessMeshPrimitive(tinygltf::Model &model,
                                      tinygltf::Primitive &primitive) {

  const int vertices_count = model.accessors[primitive.indices].count;

  // indices
  std::vector<unsigned int> indices;
  const auto *indices_array =
      getRawPrimitiveData<uint16_t>(model, primitive.indices);
  for (size_t i = 0; i < vertices_count; ++i) {
    indices.push_back(indices_array[i]);
  }

  // vertices and all attributes
  std::vector<Vertex> vertices(vertices_count);

  const auto *position_array =
      getRawPrimitiveData<float>(model, primitive.attributes["POSITION"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto &position = vertices[i].position;
    position.x = position_array[i * 3 + 0];
    position.y = position_array[i * 3 + 1];
    position.z = position_array[i * 3 + 2];
  }

  const auto *normal_array =
      getRawPrimitiveData<float>(model, primitive.attributes["NORMAL"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto &normal = vertices[i].normal;
    normal.x = normal_array[i * 3 + 0];
    normal.y = normal_array[i * 3 + 1];
    normal.z = normal_array[i * 3 + 2];
  }

  const auto *texture_coords_array =
      getRawPrimitiveData<float>(model, primitive.attributes["TEXCOORD_0"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto &tex_coords = vertices[i].tex_coords;
    tex_coords.x = texture_coords_array[i * 2 + 0];
    tex_coords.y = texture_coords_array[i * 2 + 1];
  }

  auto geometry = std::make_shared<Geometry>(vertices, indices);

  //   const auto &material = model.materials[primitive.material];
  auto material = std::make_shared<MeshFlatMaterial>();
  return std::make_shared<Mesh>("primitive", geometry, material);
}

std::shared_ptr<SceneNode> GLTFModelLoader::ProcessMesh(tinygltf::Model &model,
                                                        tinygltf::Mesh &mesh) {
  auto scene_node = std::make_shared<SceneNode>(mesh.name);
  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    auto primitive_mesh_node = ProcessMeshPrimitive(model, mesh.primitives[i]);
    scene_node->AddChild(primitive_mesh_node);
  }
  return scene_node;
}

} // namespace zen