#include "src/core/base/mesh_basic_material.h"

namespace kuro {
namespace core {

std::shared_ptr<ShaderHandle> MeshBasicMaterial::shader_handle =
    std::make_shared<ShaderHandle>("mesh_basic_shader", "mesh.vert",
                                   "mesh_basic.frag");

void render(std::shared_ptr<RenderAPI> render_api) {
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