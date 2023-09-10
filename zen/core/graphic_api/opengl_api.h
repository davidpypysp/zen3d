#pragma once

#include <GLFW/glfw3.h>

// #include <glad/glad.h>
#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

#include "zen/core/graphic_api/graphic_api.h"

namespace zen {

class OpenGLAPI : public GraphicAPI {
public:
  OpenGLAPI();

  void Init() override;

  ShaderHandle CreateShaderProgram(const std::string& vertex_path,
                                   const std::string& fragment_path,
                                   const std::string& geometry_path) override;

  void EnableShader(ShaderHandle handle) override;

  void SetShaderIntParam(ShaderHandle handle, const std::string& name,
                         const int value) override;

  void SetShaderMat4Param(ShaderHandle handle, const std::string& name,
                          const math::mat4& mat) override;

  GeometryHandle CreateGeometryInstanceWithPositions(
      const std::vector<math::vec3>& positions,
      const std::vector<unsigned int>& indices) override;

  GeometryHandle
  CreateGeometryInstance(const std::vector<Vertex>& vertices,
                         const std::vector<unsigned int>& indices) override;

  void DrawMeshInstance(GeometryHandle handle) override;

  TextureHandle CreateTextureInstance(void* data, const unsigned int width,
                                      const unsigned int height,
                                      const TextureFormat format) override;

  void EnableTextureUnit(const unsigned int unit,
                         TextureHandle handle) override;

protected:
  GLint texture_map_[3] = {GL_RED, GL_RGB, GL_RGBA};
};

} //  namespace zen
