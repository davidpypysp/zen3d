#include "gtest/gtest.h"

#include "zen/core/base/resource_manager.h"

TEST(ResourceManagerTest, BasicAssertions) {
  zen::ResourceManager<std::string> resource_manager;
  const auto key = resource_manager.Create("resource1");
  EXPECT_EQ(*resource_manager.Get(key), "resource1");

  zen::ResourceManager<double> resource_manager2;
  const auto handle = resource_manager2.Create(1.0);
  EXPECT_EQ(*resource_manager2.Get(handle), 1.0);
}
