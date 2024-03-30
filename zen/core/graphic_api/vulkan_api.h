#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "zen/core/graphic_api/graphic_api.h"
#include <optional>

namespace zen {

struct QueueFamilyIndices {
  std::optional<uint32_t> graphics_family;
  std::optional<uint32_t> present_family;

  bool IsComplete() {
    return graphics_family.has_value() && present_family.has_value();
  }
};

struct SwapChainSupportDetails {
  VkSurfaceCapabilitiesKHR capabilities;
  std::vector<VkSurfaceFormatKHR> formats;
  std::vector<VkPresentModeKHR> present_modes;
};

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

  void InitWindow();

  void InitVulkan();

  void CreateInstance();

  std::vector<const char*> GetRequiredExtensions();

  void PickPhysicalDevice();

  void CreateLogicalDevice();

  void CreateSurface();

  QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

  bool CheckDeviceExtensionSupport(VkPhysicalDevice device);

  bool IsDeviceSuitable(VkPhysicalDevice device);

  SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);

  VkSurfaceFormatKHR ChooseSwapSurfaceFormat(
      const std::vector<VkSurfaceFormatKHR>& available_formats);

  VkPresentModeKHR ChooseSwapPresentMode(
      const std::vector<VkPresentModeKHR>& available_present_modes);

  VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

  void CreateSwapChain();

  void CreateImageViews();

  VkShaderModule CreateShaderModule(const std::vector<char>& code);

  void CreateGraphicsPipeline();

  void CreateRenderPass();

  void CreateFramebuffers();

  void CreateCommandPool();

  void CreateCommandBuffer();

  void RecordCommandBuffer(VkCommandBuffer command_buffer,
                           uint32_t image_index);

  void CreateSyncObjects();

  void DrawFrame();

  void MainLoop();

  void Cleanup();

  VkInstance instance_;

  VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;

  // Logical device
  VkDevice device_;

  VkQueue graphics_queue_;

  VkQueue present_queue_;

  VkSurfaceKHR surface_;

  VkSwapchainKHR swap_chain_;

  std::vector<VkImage> swap_chain_images_;

  VkFormat swap_chain_image_format_;

  VkExtent2D swap_chain_extent_;

  VkPipelineLayout pipeline_layout_;

  VkRenderPass render_pass_;

  VkPipeline pipeline_;

  std::vector<VkImageView> swap_chain_image_views_;

  std::vector<VkFramebuffer> swap_chain_framebuffers_;

  VkCommandPool command_pool_;
  VkCommandBuffer command_buffer_;

  VkSemaphore image_available_semaphore_;
  VkSemaphore render_finished_semaphore_;
  VkFence in_flight_fence_;

  GLFWwindow* window_;

  bool enable_validation_layers_ = true;

  const std::vector<const char*> validation_layers_ = {
      "VK_LAYER_KHRONOS_validation"};

  const std::vector<const char*> device_extensions_ = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  VkDebugUtilsMessengerEXT debug_messager_;
};

} //  namespace zen
