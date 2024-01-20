#pragma once

#include "zen/core/renderer/material.h"
#include "zen/core/renderer/mesh_basic_material.h"

namespace zen {

class MaterialBuilder {
public:
  Material BuildSimpleMaterial() {
    Material material;
    // TODO: Use a shader manager to avoid loading the same shader multiple
    // times.
    material.shader = new Shader();
    material.shader->vertex_shader_path = "zen/core/shader/simple.vert";
    material.shader->fragment_shader_path = "zen/core/shader/mesh_flat.frag";
    return material;
  }

  Material BuildMeshFlatMaterial() {
    Material material;
    material.shader = new Shader();
    material.shader->vertex_shader_path = "zen/core/shader/mesh.vert";
    material.shader->fragment_shader_path = "zen/core/shader/mesh_flat.frag";
    return material;
  }

  MeshBasicMaterial BuildMeshBasicMaterial() {
    MeshBasicMaterial material;
    material.shader = new Shader();
    material.shader->vertex_shader_path = "zen/core/shader/mesh.vert";
    material.shader->fragment_shader_path = "zen/core/shader/mesh_basic.frag";
    return material;
  }
};

} // namespace zen