#pragma once

#include <memory>

#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/renderer/camera.h"

namespace zen {

struct Material {
  std::shared_ptr<ShaderProgram> shader_program;

  virtual void PrepareRender(std::shared_ptr<GraphicAPI> graphic_api,
                             std::shared_ptr<Camera> camera,
                             const math::mat4 &world_transform) {}

  virtual ~Material() {}
};

} //  namespace zen
