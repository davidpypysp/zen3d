#pragma once

#include <memory>
#include <unordered_map>

#include "zen/core/base/handle.h"
#include "zen/core/renderer/shader_program.h"

namespace zen {

class ShaderManager {
public:
  ShaderManager();

  void Init();

  std::shared_ptr<ShaderProgram>
  GetShaderProgram(std::shared_ptr<Handle> shader_handle);

  void SetShaderProgram(std::shared_ptr<Handle> shader_handle,
                        std::shared_ptr<ShaderProgram> shader_program);

protected:
  std::unordered_map<std::shared_ptr<Handle>, std::shared_ptr<ShaderProgram>>
      shader_map_;
};

} //  namespace zen
