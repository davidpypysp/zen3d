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

struct VulkanAPIVertex {
  glm::vec2 pos;
  glm::vec3 color;

  static VkVertexInputBindingDescription GetBindingDescription() {
    VkVertexInputBindingDescription binding_description = {};
    binding_description.binding = 0;
    binding_description.stride = sizeof(VulkanAPIVertex);
    binding_description.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    return binding_description;
  }

  static std::array<VkVertexInputAttributeDescription, 2>
  getAttributeDescriptions() {
    std::array<VkVertexInputAttributeDescription, 2> attribute_descriptions =
        {};

    attribute_descriptions[0].binding = 0;
    attribute_descriptions[0].location = 0;
    attribute_descriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
    attribute_descriptions[0].offset = offsetof(VulkanAPIVertex, pos);

    attribute_descriptions[1].binding = 0;
    attribute_descriptions[1].location = 1;
    attribute_descriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attribute_descriptions[1].offset = offsetof(VulkanAPIVertex, color);

    return attribute_descriptions;
  }
};

const std::vector<VulkanAPIVertex> vertices = {
    {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};

const std::vector<uint16_t> indices = {0, 1, 2, 2, 3, 0};

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

  static void FramebufferResizeCallback(GLFWwindow* window, int width,
                                        int height);

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

  void RecreateSwapChain();

  void CleanupSwapChain();

  void CreateImageViews();

  VkShaderModule CreateShaderModule(const std::vector<char>& code);

  void CreateGraphicsPipeline();

  void CreateRenderPass();

  void CreateFramebuffers();

  uint32_t FindMemoryType(uint32_t type_filter,
                          VkMemoryPropertyFlags properties);

  void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage,
                    VkMemoryPropertyFlags properties, VkBuffer& buffer,
                    VkDeviceMemory& buffer_memory);

  void CopyBuffer(VkBuffer src_buffer, VkBuffer dst_buffer, VkDeviceSize size);

  void CreateVertexBuffer();

  void CreateIndexBuffer();

  void CreateCommandPool();

  void CreateCommandBuffers();

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
  VkBuffer vertex_buffer_;
  VkDeviceMemory vertex_buffer_memory_;
  VkBuffer index_buffer_;
  VkDeviceMemory index_buffer_memory_;

  std::vector<VkCommandBuffer> command_buffers_;

  std::vector<VkSemaphore> image_available_semaphores_;
  std::vector<VkSemaphore> render_finished_semaphores_;
  std::vector<VkFence> in_flight_fences_;

  uint32_t current_frame_ = 0;

  const int kMaxFramesInFlight = 2;

  GLFWwindow* window_;

  bool enable_validation_layers_ = true;

  const std::vector<const char*> validation_layers_ = {
      "VK_LAYER_KHRONOS_validation"};

  const std::vector<const char*> device_extensions_ = {
      VK_KHR_SWAPCHAIN_EXTENSION_NAME};

  VkDebugUtilsMessengerEXT debug_messager_;

  bool framebuffer_resized_ = false;
};

} //  namespace zen
