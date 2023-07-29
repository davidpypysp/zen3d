#pragma once

#include <GLFW/glfw3.h>

// #include <glad/glad.h>
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "zen/core/graphic_api/graphic_api.h"
#include "zen/core/graphic_api/shader_program.h"
#include "zen/core/graphic_api/vertex.h"

namespace zen {

struct GLSLShaderProgram : public ShaderProgram {
  unsigned int id;
};

struct GLGeometryHandle : public GeometryHandle {
  unsigned int vao;
  unsigned int vbo;
  unsigned int ebo;
  unsigned int size;
};

struct GLTextureHandle : public TextureHandle {
  unsigned int id;
};

class OpenGLAPI : public GraphicAPI {
public:
  OpenGLAPI();

  void Init();
  std::shared_ptr<ShaderProgram> CreateShaderProgram(const char *vertex_path,
                                                     const char *fragment_path,
                                                     const char *geometry_path);
  void EnableShaderProgram(std::shared_ptr<ShaderProgram> program);
  void SetShaderIntParam(std::shared_ptr<ShaderProgram> program,
                         const std::string &name, const int value);
  void SetShaderMat4Param(std::shared_ptr<ShaderProgram> program,
                          const std::string &name, const math::mat4 &mat);

  std::shared_ptr<GeometryHandle>
  CreateGeometryInstanceWithPositions(const std::vector<math::vec3> &positions,
                                      const std::vector<unsigned int> &indices);
  std::shared_ptr<GeometryHandle>
  CreateGeometryInstance(const std::vector<Vertex> &vertices,
                         const std::vector<unsigned int> &indices);

  void DrawMeshInstance(std::shared_ptr<GeometryHandle> handle);

  std::shared_ptr<TextureHandle>
  CreateTextureInstance(void *data, const unsigned int width,
                        const unsigned int height, const TextureFormat format);

  void EnableTextureUnit(const unsigned int unit = 0,
                         std::shared_ptr<TextureHandle> handle = nullptr);

protected:
  static constexpr GLint texture_map_[] = {GL_RED, GL_RGB, GL_RGBA};
};

} //  namespace zen
