#include <gtest/gtest.h>

#include "zen/core/graphic_api/vulkan_api.h"

TEST(VulkanAPI, BasicAssertions) {
  zen::VulkanAPI vulkan_api;
  vulkan_api.Init();
}
