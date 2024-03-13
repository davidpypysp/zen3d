#include "zen/core/graphic_api/vulkan_api.h"
#include "zen/core/base/logging.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cstring> 
#include "vulkan_api.h"

namespace zen {

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}


QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphics_family = i;
        }

        if (indices.IsComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool IsDeviceSuitable(VkPhysicalDevice device) {
    QueueFamilyIndices indices = FindQueueFamilies(device);
    return indices.IsComplete();
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {

    void *userData = pUserData;


    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}




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

    CreateInstance();

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
}

std::vector<const char*> VulkanAPI::GetRequiredExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);


    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enable_validation_layers_) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void VulkanAPI::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
}

void VulkanAPI::SetupDebugMessenger() {
  if (!enable_validation_layers_) return;

  VkDebugUtilsMessengerCreateInfoEXT createInfo;
  PopulateDebugMessengerCreateInfo(createInfo);

  if (CreateDebugUtilsMessengerEXT(instance_, &createInfo, nullptr, &debug_messager_) != VK_SUCCESS) {
      throw std::runtime_error("failed to set up debug messenger!");
  }

}


bool VulkanAPI::CheckValidationLayerSupport() {
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

  std::vector<VkLayerProperties> availableLayers(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

  for(const char* layerName : validation_layers_) {
    bool layerFound = false;
    for(const auto& layerProperties : availableLayers) {
      if(strcmp(layerName, layerProperties.layerName) == 0) {
        layerFound = true;
        break;
      }
    }

    if (!layerFound)
    {
      return false;
    }
    
  }

  return true;

}

void VulkanAPI::CreateInstance() {
  if(enable_validation_layers_ && !CheckValidationLayerSupport()) {
    throw std::runtime_error("Validation layers requested, but not available!");
  }

  // appInfo;
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Triangle";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  //  createInfo;
  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  uint32_t glfwExtensionCount = 0;
  const char** glfwExtensions;
  glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;
  createInfo.enabledLayerCount = 0;


  if(enable_validation_layers_) {
    createInfo.enabledLayerCount = static_cast<uint32_t>(validation_layers_.size());
    createInfo.ppEnabledLayerNames = validation_layers_.data();
  } else {
    createInfo.enabledLayerCount = 0;
  }

  VkResult result = vkCreateInstance(&createInfo, nullptr, &instance_);
  if(result != VK_SUCCESS) {
    throw std::runtime_error("failed to create vk instance!");
  }
  LOG(Info) << "Create instance success!";

}

void VulkanAPI::PickPhysicalDevice() {
  uint32_t device_count = 0;
  vkEnumeratePhysicalDevices(instance_, &device_count, nullptr);
  if(device_count == 0) {
    throw std::runtime_error("failed to find GPUs with Vulkan support!");
  }

  std::vector<VkPhysicalDevice> devices(device_count);
  vkEnumeratePhysicalDevices(instance_, &device_count, devices.data());

  for (const auto& device : devices) {
      if (IsDeviceSuitable(device)) {
          physical_device_ = device;
          break;
      }
  }

  if (physical_device_ == VK_NULL_HANDLE) {
      throw std::runtime_error("failed to find a suitable GPU!");
  }
}

void VulkanAPI::Cleanup() {
  if(enable_validation_layers_) {
    DestroyDebugUtilsMessengerEXT(instance_, debug_messager_, nullptr);
  }
  vkDestroyInstance(instance_, nullptr);
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