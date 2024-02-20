#pragma once

#include "zen/core/base/transform.h"
#include "zen/core/graphic_api/texture.h"
#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/material.h"

namespace zen {

struct MeshBasicMaterial : public Material {
  // static params
  TextureHandle diffuse_map_handle;
  TextureHandle specular_map_handle;
  TextureHandle normal_map_handle;
  TextureHandle height_map_handle;

  // dynamic params
  math::mat4 geometry_world_position;

  // reference
  Camera* camera = nullptr;
  Transform* camera_transform = nullptr;

  void SetupShaderParams(GraphicAPI& graphic_api) override {
    graphic_api.SetShaderMat4Param(shader->handle, "model",
                                   geometry_world_position);

    // TODO: refactor this
    constexpr float kRatio = 3600.0 / 1800.0;
    graphic_api.SetShaderMat4Param(shader->handle, "projection",
                                   camera->GetPerspectiveMatrix(kRatio));
    graphic_api.SetShaderMat4Param(
        shader->handle, "view",
        camera->GetViewMatrix(camera_transform->WorldPosition()));

    // use material
    graphic_api.SetShaderIntParam(shader->handle, "texture_diffuse", 0);
    graphic_api.EnableTextureUnit(0, diffuse_map_handle);

    graphic_api.SetShaderIntParam(shader->handle, "texture_specular", 1);
    graphic_api.EnableTextureUnit(1, specular_map_handle);

    graphic_api.SetShaderIntParam(shader->handle, "texture_normal", 2);
    graphic_api.EnableTextureUnit(2, normal_map_handle);

    graphic_api.SetShaderIntParam(shader->handle, "texture_height", 3);
    graphic_api.EnableTextureUnit(3, height_map_handle);
  }
};

} //  namespace zen
