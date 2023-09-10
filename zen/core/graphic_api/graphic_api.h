#pragma once

#include <memory>
#include <vector>

#include "zen/core/graphic_api/geometry_handle.h"
#include "zen/core/graphic_api/shader.h"
#include "zen/core/graphic_api/texture.h"
#include "zen/core/graphic_api/vertex.h"

namespace zen {

class GraphicAPI {
public:
  GraphicAPI(){};

  virtual ~GraphicAPI() = default;

  virtual void Init() = 0;

  virtual ShaderHandle
  CreateShaderProgram(const std::string& vertex_path,
                      const std::string& fragment_path,
                      const std::string& geometry_path = "") = 0;

  virtual void EnableShader(ShaderHandle handle) = 0;

  virtual void SetShaderIntParam(ShaderHandle handle, const std::string& name,
                                 const int value) = 0;

  virtual void SetShaderMat4Param(ShaderHandle handle, const std::string& name,
                                  const math::mat4& mat) = 0;

  virtual GeometryHandle CreateGeometryInstanceWithPositions(
      const std::vector<math::vec3>& positions,
      const std::vector<unsigned int>& indices) = 0;

  virtual GeometryHandle
  CreateGeometryInstance(const std::vector<Vertex>& vertices,
                         const std::vector<unsigned int>& indices) = 0;

  virtual void DrawMeshInstance(GeometryHandle handle) = 0;

  virtual TextureHandle CreateTextureInstance(void* data,
                                              const unsigned int width,
                                              const unsigned int height,
                                              const TextureFormat format) = 0;
  virtual void EnableTextureUnit(const unsigned int unit,
                                 TextureHandle handle) = 0;
};

} //  namespace zen
