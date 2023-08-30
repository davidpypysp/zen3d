// TODO: add thsi system
void MeshBasicMaterial::PrepareRender(std::shared_ptr<GraphicAPI> graphic_api,
                                      std::shared_ptr<Camera> camera,
                                      const math::mat4& world_transform) {
  graphic_api->SetShaderMat4Param(shader_program, "model", world_transform);

  // TODO: refactor this
  constexpr float kRatio = 3600.0 / 1800.0;
  graphic_api->SetShaderMat4Param(shader_program, "projection",
                                  camera->GetPerspectiveMatrix(kRatio));
  graphic_api->SetShaderMat4Param(shader_program, "view",
                                  camera->GetViewMatrix());

  // use material
  unsigned int texture_num = 0;
  if (diffuse_map) {
    graphic_api->SetShaderIntParam(shader_program, "texture_diffuse",
                                   texture_num);
    graphic_api->EnableTextureUnit(texture_num++, diffuse_map->handle);
  }
  if (specular_map) {
    graphic_api->SetShaderIntParam(shader_program, "texture_specular",
                                   texture_num);
    graphic_api->EnableTextureUnit(texture_num++, specular_map->handle);
  }
  if (normal_map) {
    graphic_api->SetShaderIntParam(shader_program, "texture_normal",
                                   texture_num);
    graphic_api->EnableTextureUnit(texture_num++, normal_map->handle);
  }
  if (height_map) {
    graphic_api->SetShaderIntParam(shader_program, "texture_height",
                                   texture_num);
    graphic_api->EnableTextureUnit(texture_num++, height_map->handle);
  }
}