#ifndef CORE_BASE_MESH_BASIC_MATERIAL_H_
#define CORE_BASE_MESH_BASIC_MATERIAL_H_

#include "src/core/base/material.h"
#include "src/core/base/texture.h"

namespace kuro {
namespace core {

struct MeshBasicMaterial : public Material {
  std::shared_ptr<Texture> diffuse_map;
  std::shared_ptr<Texture> specular_map;
  std::shared_ptr<Texture> normal_map;
  std::shared_ptr<Texture> height_map;

  void render(std::shared_ptr<RenderAPI> render_api) override;
};

} // namespace core
} //  namespace kuro

#endif