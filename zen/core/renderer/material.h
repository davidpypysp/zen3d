#pragma once

#include <memory>

#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/graphic_api/shader.h"

namespace zen {

struct Material {
  Shader* shader;

  void Enable(GraphicAPI& graphic_api) {
    graphic_api.EnableShader(shader);
    SetupShaderParams(graphic_api);
  }

  virtual void SetupShaderParams(GraphicAPI& graphic_api) {}
};

} //  namespace zen
