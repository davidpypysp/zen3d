#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "zen/core/graphic_api/graphic_api.h"

namespace zen {



class VulkanAPI : public GraphicAPI {
public:
  VulkanAPI();

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

  // Vulkan specific
  void SetupDebugMessenger();

  void PopulateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT& createInfo);

  bool CheckValidationLayerSupport();

  void CreateInstance();

  std::vector<const char*> GetRequiredExtensions();

  void Cleanup();

  VkInstance instance_;

  bool enable_validation_layers_ = true;

  const std::vector<const char*> validation_layers_ = {
      "VK_LAYER_LUNARG_standard_validation"};
  
   VkDebugUtilsMessengerEXT debug_messager_;
};

} //  namespace zen
