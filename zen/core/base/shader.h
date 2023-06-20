#pragma once

#include <memory>
#include <string>

#include "zen/core/math/math.h"

namespace zen {

struct ShaderProgram {};

class Shader {
public:
  Shader(const char *vertex_path, const char *fragment_path,
         const char *geometry_path = nullptr);

  void Use();

  // utility uniform functions
  void SetInt(const std::string &name, const int value);
  void SetMat4(const std::string &name, const math::mat4 &mat);

private:
  std::shared_ptr<ShaderProgram> shader_program_;
};

} //  namespace zen
