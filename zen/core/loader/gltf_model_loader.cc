// tiny gltf define should be in .cc file
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "zen/core/loader/gltf_model_loader.h"

#include "zen/core/base/logging.h"
#include "zen/core/base/transform.h"

namespace zen {

GLTFModelLoader::GLTFModelLoader() {}

void GLTFModelLoader::LoadModel(const std::string& path, Scene& scene) {
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

  const tinygltf::Scene& gltf_scene = model.scenes[model.defaultScene];
  auto root_entity = scene.AddEntity("root");
  for (size_t i = 0; i < gltf_scene.nodes.size(); ++i) {
    auto& node = model.nodes[gltf_scene.nodes[i]];
    ProcessNode(model, node, scene, root_entity);
  }
}

void GLTFModelLoader::ProcessNode(tinygltf::Model& model, tinygltf::Node& node,
                                  Scene& scene, EntityHandle parent) {
  auto entity = scene.AddEntity(node.name);
  if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
    auto& mesh = model.meshes[node.mesh];
    ProcessMesh(model, mesh, scene, entity);
  }
  for (size_t i = 0; i < node.children.size(); i++) {
    ProcessNode(model, model.nodes[node.children[i]], scene, entity);
  }
}

void GLTFModelLoader::ProcessMesh(tinygltf::Model& model, tinygltf::Mesh& mesh,
                                  Scene& scene, EntityHandle entity) {
  for (size_t i = 0; i < mesh.primitives.size(); ++i) {
    scene.emplace<Transform>(entity, math::vec3(0, 0, 0));
    Geometry geometry = ProcessMeshPrimitive(model, mesh.primitives[i]);
    //   const auto &material = model.materials[primitive.material];
    // flat material
    Material material{"zen/core/shader/simple.vert",
                      "zen/core/shader/mesh_flat.frag"};
    scene.emplace<Mesh>(entity, mesh.name, geometry, material);

    // TODO: add material
    break;
  }
}

Geometry GLTFModelLoader::ProcessMeshPrimitive(tinygltf::Model& model,
                                               tinygltf::Primitive& primitive) {

  const int vertices_count = model.accessors[primitive.indices].count;

  // indices
  std::vector<unsigned int> indices;
  const auto* indices_array =
      getRawPrimitiveData<uint16_t>(model, primitive.indices);
  for (size_t i = 0; i < vertices_count; ++i) {
    indices.push_back(indices_array[i]);
  }

  // vertices and all attributes
  std::vector<Vertex> vertices(vertices_count);

  const auto* position_array =
      getRawPrimitiveData<float>(model, primitive.attributes["POSITION"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto& position = vertices[i].position;
    position.x = position_array[i * 3 + 0];
    position.y = position_array[i * 3 + 1];
    position.z = position_array[i * 3 + 2];
  }

  const auto* normal_array =
      getRawPrimitiveData<float>(model, primitive.attributes["NORMAL"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto& normal = vertices[i].normal;
    normal.x = normal_array[i * 3 + 0];
    normal.y = normal_array[i * 3 + 1];
    normal.z = normal_array[i * 3 + 2];
  }

  const auto* texture_coords_array =
      getRawPrimitiveData<float>(model, primitive.attributes["TEXCOORD_0"]);
  for (size_t i = 0; i < vertices_count; ++i) {
    auto& tex_coords = vertices[i].tex_coords;
    tex_coords.x = texture_coords_array[i * 2 + 0];
    tex_coords.y = texture_coords_array[i * 2 + 1];
  }
  return Geometry{vertices, indices};
}

} // namespace zen