#pragma once

#include <string>

namespace zen {

struct ShaderProgram {
  ShaderProgram() {}

  ShaderProgram(const std::string &name, const std::string &vertex_shader_path,
                const std::string &fragment_shader_path,
                const std::string &geometry_shader_path = "")
      : name(name), vertex_shader_path(vertex_shader_path),
        fragment_shader_path(fragment_shader_path),
        geometry_shader_path(geometry_shader_path) {}

  std::string name;
  std::string vertex_shader_path;
  std::string fragment_shader_path;
  std::string geometry_shader_path;

  unsigned int id;
};

} //  namespace zen
