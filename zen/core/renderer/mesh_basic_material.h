#pragma once

#include "zen/core/renderer/material.h"
#include "zen/core/renderer/texture.h"

namespace zen {

struct MeshBasicMaterial : public Material {
  std::shared_ptr<Texture> diffuse_map;
  std::shared_ptr<Texture> specular_map;
  std::shared_ptr<Texture> normal_map;
  std::shared_ptr<Texture> height_map;

  MeshBasicMaterial();

  void InitShaderProgram(std::shared_ptr<GraphicAPI> graphic_api) override;

  void PrepareRender(std::shared_ptr<GraphicAPI> graphic_api,
                     std::shared_ptr<Camera> camera,
                     const math::mat4 &world_transform) override;
};

} //  namespace zen
