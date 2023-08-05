#pragma once

#include <GLFW/glfw3.h>

// #include <glad/glad.h>
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

#include "zen/core/graphic_api/graphic_api.h"

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

  void Init() override;

  std::shared_ptr<ShaderProgram>
  CreateShaderProgram(const std::string &vertex_path,
                      const std::string &fragment_path,
                      const std::string &geometry_path) override;

  void EnableShaderProgram(std::shared_ptr<ShaderProgram> program) override;

  void SetShaderIntParam(std::shared_ptr<ShaderProgram> program,
                         const std::string &name, const int value) override;

  void SetShaderMat4Param(std::shared_ptr<ShaderProgram> program,
                          const std::string &name,
                          const math::mat4 &mat) override;

  std::shared_ptr<GeometryHandle> CreateGeometryInstanceWithPositions(
      const std::vector<math::vec3> &positions,
      const std::vector<unsigned int> &indices) override;

  std::shared_ptr<GeometryHandle>
  CreateGeometryInstance(const std::vector<Vertex> &vertices,
                         const std::vector<unsigned int> &indices) override;

  void DrawMeshInstance(std::shared_ptr<GeometryHandle> handle) override;

  std::shared_ptr<TextureHandle>
  CreateTextureInstance(void *data, const unsigned int width,
                        const unsigned int height,
                        const TextureFormat format) override;

  void
  EnableTextureUnit(const unsigned int unit = 0,
                    std::shared_ptr<TextureHandle> handle = nullptr) override;

protected:
  GLint texture_map_[3] = {GL_RED, GL_RGB, GL_RGBA};

  std::unordered_map<std::string, std::shared_ptr<ShaderProgram>>
      shader_programs_;
};

} //  namespace zen
