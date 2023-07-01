#pragma once

#include <memory>

#include "zen/core/renderer/camera.h"
#include "zen/core/renderer/render_api.h"
#include "zen/core/renderer/shader_program.h"

namespace zen {

struct Material {
  std::shared_ptr<ShaderProgram> shader_program;

  virtual void PrepareRender(std::shared_ptr<RenderAPI> render_api,
                             std::shared_ptr<Camera> camera,
                             const math::vec3 &camera_position,
                             const math::mat4 &world_transform) {}

  virtual ~Material() {}
};

} //  namespace zen
