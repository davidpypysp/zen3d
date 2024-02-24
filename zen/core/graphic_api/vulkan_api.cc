#include "zen/core/graphic_api/vulkan_api.h"
#include "zen/core/base/logging.h"

#include <fstream>
#include <sstream>
#include <string>

namespace zen {

VulkanAPI::VulkanAPI() : GraphicAPI() {}

void VulkanAPI::Init() { 
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}

ShaderHandle VulkanAPI::CreateShaderProgram(const std::string& vertex_path,
                                            const std::string& fragment_path,
                                            const std::string& geometry_path) {
  ShaderHandle handle;
  return handle;
}

void VulkanAPI::EnableShader(ShaderHandle handle) {  }

/**
 *
 */
void VulkanAPI::SetShaderIntParam(ShaderHandle handle, const std::string& name,
                                  const int value) {
}

void VulkanAPI::SetShaderMat4Param(ShaderHandle handle, const std::string& name,
                                   const math::mat4& mat) {
}

GeometryHandle VulkanAPI::CreateGeometryInstanceWithPositions(
    const std::vector<math::vec3>& positions,
    const std::vector<unsigned int>& indices) {
  GeometryHandle handle;
  return handle;
}

GeometryHandle
VulkanAPI::CreateGeometryInstance(const std::vector<Vertex>& vertices,
                                  const std::vector<unsigned int>& indices) {
  GeometryHandle handle;
  return handle;
}

void VulkanAPI::DrawMeshInstance(GeometryHandle handle) {
}

TextureHandle VulkanAPI::CreateTextureInstance(void* data,
                                               const unsigned int width,
                                               const unsigned int height,
                                               const TextureFormat format) {
  TextureHandle handle;
  return handle;
}

void VulkanAPI::EnableTextureUnit(const unsigned int unit,
                                  TextureHandle handle) {
}

} //  namespace zen