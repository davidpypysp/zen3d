#pragma once

#include <memory>

#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/renderer/camera.h"

namespace zen {

struct Material {
  std::string vertex_shader_path;
  std::string fragment_shader_path;
  std::shared_ptr<ShaderProgram> shader_program;
};

} //  namespace zen
