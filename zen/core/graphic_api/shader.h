#pragma once

#include <string>

namespace zen {

struct ShaderHandle {
  // TODO #if on vulkan
  unsigned int id;
};

struct Shader {
  Shader() {}

  std::string vertex_shader_path;
  std::string fragment_shader_path;

  ShaderHandle handle;
  std::string name;
};

} //  namespace zen
