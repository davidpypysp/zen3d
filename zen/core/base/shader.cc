#include "zen/core/base/shader.h"

namespace zen {

Shader::Shader(const char *vertex_path, const char *fragment_path,
               const char *geometry_path) {
  //   shader_program_ = Engine::GetRenderAPI()->CreateShaderProgram(
  //       vertex_path, fragment_path, geometry_path);
}

void Shader::Use() {
  //   Engine::GetRenderAPI()->EnableShaderProgram(shader_program_);
}

void Shader::SetInt(const std::string &name, const int value) {
  //   Engine::GetRenderAPI()->SetShaderIntParam(shader_program_, name, value);
}

void Shader::SetMat4(const std::string &name, const math::mat4 &mat) {
  //   Engine::GetRenderAPI()->SetShaderMat4Param(shader_program_, name, mat);
}

} //  namespace zen