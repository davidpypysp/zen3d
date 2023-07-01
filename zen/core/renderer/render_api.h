#pragma once

#include <memory>
#include <vector>

#include "zen/core/renderer/shader_program.h"
#include "zen/core/renderer/texture.h"
#include "zen/core/renderer/vertex.h"

namespace zen {

class RenderAPI {
public:
  RenderAPI(){};

  virtual ~RenderAPI() = default;

  virtual void Init() = 0;

  virtual std::shared_ptr<ShaderProgram>
  CreateShaderProgram(const char *vertex_path, const char *fragment_path,
                      const char *geometry_path = nullptr) = 0;

  virtual void EnableShaderProgram(std::shared_ptr<ShaderProgram> program) = 0;

  virtual void SetShaderIntParam(std::shared_ptr<ShaderProgram> program,
                                 const std::string &name, const int value) = 0;

  virtual void SetShaderMat4Param(std::shared_ptr<ShaderProgram> program,
                                  const std::string &name,
                                  const math::mat4 &mat) = 0;

  virtual std::shared_ptr<Handle> CreateGeometryInstanceWithPositions(
      const std::vector<math::vec3> &positions,
      const std::vector<unsigned int> &indices) = 0;

  virtual std::shared_ptr<Handle>
  CreateGeometryInstance(const std::vector<Vertex> &vertices,
                         const std::vector<unsigned int> &indices) = 0;

  virtual void DrawMeshInstance(std::shared_ptr<Handle> handle) = 0;

  virtual std::shared_ptr<Handle>
  CreateTextureInstance(void *data, const unsigned int width,
                        const unsigned int height,
                        const TextureFormat format) = 0;
  virtual void EnableTextureUnit(const unsigned int unit = 0,
                                 std::shared_ptr<Handle> handle = nullptr) = 0;
};

} //  namespace zen
