#include <gtest/gtest.h>

#include "zen/core/base/scene.h"

struct Position {
  float x;
  float y;
};

struct Velocity {
  float x;
  float y;
};

TEST(SceneTest, BasicAssertions) {
  zen::Scene scene;

  auto& entity = scene.CreateEntity();
  entity.AddComponent<Position>(1.0f, 2.0f);

  auto& entity2 = scene.CreateEntity();
  entity2.AddComponent<Position>(3.0f, 4.0f);
  entity2.AddComponent<Velocity>(5.0f, 6.0f);

  const auto& view = scene.View<Position, Velocity>();

  for (const auto& [entity, position, velocity] : view.each()) {
    std::cout << "position: " << position.x << ", " << position.y << std::endl;
    std::cout << "velocity: " << velocity.x << ", " << velocity.y << std::endl;
  }
}
