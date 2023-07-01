#pragma once

#include <memory>

#include "zen/core/renderer/render_api.h"
#include "zen/core/renderer/shader_program.h"

namespace zen {

struct Material {
  std::shared_ptr<ShaderProgram> shader_program;

  virtual void render(std::shared_ptr<RenderAPI> render_api) = 0;

  virtual ~Material() {}
};

} //  namespace zen
