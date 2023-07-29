#include "src/core/base/mesh_basic_material.h"

namespace kuro {
namespace core {

MeshBasicMaterial::MeshBasicMaterial() {
  constexpr auto mesh_vert_shader = "zen/core/shader/mesh.vert";
  constexpr auto mesh_frag_shader = "zen/core/shader/mesh_basic.frag";
  shader_program = std::make_shared<ShaderProgram>(
      "mesh_basic_shader", mesh_vert_shader, mesh_vert_shader);
};

void PrepareRender(std::shared_ptr<GraphicAPI> render_api,
                   std::shared_ptr<Camera> camera,
                   const math::mat4 &world_transform) {
  render_api->SetShaderMat4Param(shader_program, "model", world_transform);
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