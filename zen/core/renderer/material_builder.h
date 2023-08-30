#pragma once

#include "zen/core/renderer/material.h"
#include "zen/core/renderer/mesh_basic_material.h"

namespace zen {

class MaterialBuilder {
public:
  Material BuildSimpleMaterial() {
    Material material;
    material.vertex_shader_path = "zen/core/shader/simple.vert";
    material.fragment_shader_path = "zen/core/shader/mesh_flat.frag";
    return material;
  }

  Material BuildMeshFlatMaterial() {
    Material material;
    material.vertex_shader_path = "zen/core/shader/mesh.vert";
    material.fragment_shader_path = "zen/core/shader/mesh_flat.frag";
    return material;
  }

  MeshBasicMaterial BuildMeshBasicMaterial() {
    MeshBasicMaterial material;
    material.vertex_shader_path = "zen/core/shader/mesh.vert";
    material.fragment_shader_path = "zen/core/shader/mesh_basic.frag";
    return material;
  }
};

} // namespace zen