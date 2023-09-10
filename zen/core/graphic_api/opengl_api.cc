#include "zen/core/graphic_api/opengl_api.h"
#include "zen/core/base/logging.h"

#include <fstream>
#include <sstream>
#include <string>

namespace zen {

void CheckCompileErrors(GLuint shader, std::string type) {
  GLint success;
  GLchar infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, 1024, NULL, infoLog);
      LOG(Error)
          << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- ";
    }
  } else {
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader, 1024, NULL, infoLog);
      LOG(Error)
          << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n"
          << infoLog
          << "\n -- --------------------------------------------------- -- ";
    }
  }
}

GLint GetShaderParam(ShaderHandle handle, const std::string& param) {
  return glGetUniformLocation(handle.id, param.c_str());
}

OpenGLAPI::OpenGLAPI() : GraphicAPI() {}

void OpenGLAPI::Init() { glEnable(GL_DEPTH_TEST); }

ShaderHandle OpenGLAPI::CreateShaderProgram(const std::string& vertex_path,
                                            const std::string& fragment_path,
                                            const std::string& geometry_path) {

  std::string vertex_code;
  std::string fragment_code;
  std::string geometry_code;

  std::ifstream vshader_file;
  std::ifstream fshader_file;
  std::ifstream gshader_file;

  vshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  gshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  // TODO: exception special handling for wasm
  vshader_file.open(vertex_path);
  fshader_file.open(fragment_path);
  std::stringstream vshader_stream, fshader_stream;

  vshader_stream << vshader_file.rdbuf();
  fshader_stream << fshader_file.rdbuf();

  vshader_file.close();
  fshader_file.close();

  vertex_code = vshader_stream.str();
  fragment_code = fshader_stream.str();
  if (!geometry_path.empty()) {
    gshader_file.open(geometry_path);
    std::stringstream gshader_stream;
    gshader_stream << gshader_file.rdbuf();
    gshader_file.close();
    geometry_code = gshader_stream.str();
  }

  const char* vshader_code = vertex_code.c_str();
  const char* fshader_code = fragment_code.c_str();
  // 2. compile shaders
  unsigned int vertex, fragment;
  // vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vshader_code, NULL);
  glCompileShader(vertex);
  CheckCompileErrors(vertex, "VERTEX");
  // fragment Shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fshader_code, NULL);
  glCompileShader(fragment);
  CheckCompileErrors(fragment, "FRAGMENT");
  // if geometry shader is given, compile geometry shader
  unsigned int geometry;
  if (!geometry_path.empty()) {
    const char* gshader_code = geometry_code.c_str();
    geometry = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry, 1, &gshader_code, NULL);
    glCompileShader(geometry);
    CheckCompileErrors(geometry, "GEOMETRY");
  }

  // TODO: clean this
  // auto shader = std::make_shared<GLSLShaderProgram>();
  // shader->name = shader_hash;

  ShaderHandle handle;

  // shader Program
  handle.id = glCreateProgram();
  glAttachShader(handle.id, vertex);
  glAttachShader(handle.id, fragment);
  if (!geometry_path.empty()) {
    glAttachShader(handle.id, geometry);
  }
  glLinkProgram(handle.id);
  CheckCompileErrors(handle.id, "PROGRAM");
  // delete the shaders as they're linked into our program now and no longer
  // necessery
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  if (!geometry_path.empty()) {
    glDeleteShader(geometry);
  }

  return handle;
}

void OpenGLAPI::EnableShader(ShaderHandle handle) { glUseProgram(handle.id); }

/**
 *
 */
void OpenGLAPI::SetShaderIntParam(ShaderHandle handle, const std::string& name,
                                  const int value) {
  glUniform1i(GetShaderParam(handle, name), value);
}

void OpenGLAPI::SetShaderMat4Param(ShaderHandle handle, const std::string& name,
                                   const math::mat4& mat) {
  glUniformMatrix4fv(GetShaderParam(handle, name), 1, GL_FALSE, &mat[0][0]);
}

GeometryHandle OpenGLAPI::CreateGeometryInstanceWithPositions(
    const std::vector<math::vec3>& positions,
    const std::vector<unsigned int>& indices) {
  GeometryHandle handle;
  handle.vertex_size = indices.size();

  glGenVertexArrays(1, &handle.vao);
  glGenBuffers(1, &handle.vbo);
  glGenBuffers(1, &handle.ebo);

  glBindVertexArray(handle.vao);
  glBindBuffer(GL_ARRAY_BUFFER, handle.vbo);
  glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(math::vec3),
               &positions[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), (void*)0);

  glBindVertexArray(0);
  return handle;
}

GeometryHandle
OpenGLAPI::CreateGeometryInstance(const std::vector<Vertex>& vertices,
                                  const std::vector<unsigned int>& indices) {
  GeometryHandle handle;
  handle.vertex_size = indices.size();

  glGenVertexArrays(1, &handle.vao);
  glGenBuffers(1, &handle.vbo);
  glGenBuffers(1, &handle.ebo);

  glBindVertexArray(handle.vao);
  glBindBuffer(GL_ARRAY_BUFFER, handle.vbo);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0],
               GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
               &indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, normal));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, tex_coords));

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, tangent));

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                        (void*)offsetof(Vertex, bitangent));
  glBindVertexArray(0);
  return handle;
}

void OpenGLAPI::DrawMeshInstance(GeometryHandle handle) {
  glBindVertexArray(handle.vao);
  glDrawElements(GL_TRIANGLES, handle.vertex_size, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

TextureHandle OpenGLAPI::CreateTextureInstance(void* data,
                                               const unsigned int width,
                                               const unsigned int height,
                                               const TextureFormat format) {
  TextureHandle handle;
  glGenTextures(1, &(handle.id));

  glBindTexture(GL_TEXTURE_2D, handle.id);

  auto gl_format = texture_map_[format];

  glTexImage2D(GL_TEXTURE_2D, 0, gl_format, width, height, 0, gl_format,
               GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  return handle;
}

void OpenGLAPI::EnableTextureUnit(const unsigned int unit,
                                  TextureHandle handle) {
  glActiveTexture(GL_TEXTURE0 + unit);
  glBindTexture(GL_TEXTURE_2D, handle.id);
}

} //  namespace zen