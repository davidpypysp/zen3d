#include "zen/core/renderer/shader_manager.h"

namespace zen {

ShaderManager::ShaderManager() {}

std::shared_ptr<ShaderProgram>
ShaderManager::GetShaderProgram(std::shared_ptr<Handle> handle) {
  return shader_map_[handle];
}

void ShaderManager::SetShaderProgram(std::shared_ptr<Handle> handle,
                                     std::shared_ptr<ShaderProgram> program) {
  shader_map_[handle] = program;
}

} //  namespace zen