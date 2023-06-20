#pragma once

#include <memory>

#include "zen/core/base/shader.h"

namespace zen {

struct Material {
  virtual std::shared_ptr<Shader> GetShader() = 0;

  virtual ~Material() {}
};

} //  namespace zen
