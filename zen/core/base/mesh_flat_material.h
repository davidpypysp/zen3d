#pragma once

#include "zen/core/base/material.h"

namespace zen {

struct MeshFlatMaterial : public Material {
  static std::shared_ptr<Shader> shader;

  std::shared_ptr<Shader> GetShader() { return shader; }
};

} //  namespace zen
