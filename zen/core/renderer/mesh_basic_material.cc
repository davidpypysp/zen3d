#include "src/core/base/mesh_basic_material.h"

namespace kuro {
namespace core {

MeshBasicMaterial::MeshBasicMaterial() {
  shader_program = std::make_shared<ShaderProgram>(
      "mesh_basic_shader", "data/mesh.vert", "data/mesh_basic.frag");
};

void PrepareRender(std::shared_ptr<RenderAPI> render_api,
                   std::shared_ptr<Camera> camera,
                   const math::vec3 &camera_position,
                   const math::vec3 &position) {
  // use material
  unsigned int texture_num = 0;
  if (mesh_basic_material->diffuse_map) {
    render_api_->SetShaderIntParam(shader_program, "texture_diffuse",
                                   texture_num);
    render_api_->EnableTextureUnit(texture_num++,
                                   mesh_basic_material->diffuse_map->handle);
  }
  if (mesh_basic_material->specular_map) {
    render_api_->SetShaderIntParam(shader_program, "texture_specular",
                                   texture_num);
    render_api_->EnableTextureUnit(texture_num++,
                                   mesh_basic_material->specular_map->handle);
  }
  if (mesh_basic_material->normal_map) {
    render_api_->SetShaderIntParam(shader_program, "texture_normal",
                                   texture_num);
    render_api_->EnableTextureUnit(texture_num++,
                                   mesh_basic_material->normal_map->handle);
  }
  if (mesh_basic_material->height_map) {
    render_api_->SetShaderIntParam(shader_program, "texture_height",
                                   texture_num);
    render_api_->EnableTextureUnit(texture_num++,
                                   mesh_basic_material->height_map->handle);
  }
}

} // namespace core
} //  namespace kuro