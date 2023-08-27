
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <iostream>

#include <entt/entt.hpp>

struct position {
  float x;
  float y;
};

struct velocity {
  float dx;
  float dy;
};

void update(entt::registry &registry) {
  auto view = registry.view<const position, velocity>();

  // use a callback
  view.each([](const auto &pos, auto &vel) { /* ... */ });

  // use an extended callback
  view.each([](const auto entity, const auto &pos, auto &vel) { /* ... */ });

  // use a range-for
  for (auto [entity, pos, vel] : view.each()) {
    std::cout << "pos: " << pos.x << ", " << pos.y << std::endl;
    std::cout << "vel: " << vel.dx << ", " << vel.dy << std::endl;
    // ...
  }

  // use forward iterators and get only the components of interest
  for (auto entity : view) {
    auto &vel = view.get<velocity>(entity);
    std::cout << "single vel: " << vel.dx << ", " << vel.dy << std::endl;
    // ...
  }

  for (auto entity : view) {
    const auto &position = view.get<const struct position>(entity);
    std::cout << "single position: " << position.x << ", " << position.y
              << std::endl;
    // ...
  }

  auto view2 = registry.view<const position>();
  for (auto [entity, pos] : view2.each()) {
    std::cout << "view2 pos: " << pos.x << ", " << pos.y << std::endl;
    // ...
  }
}

void loop() {}

extern "C" int main(int argc, char **argv) {
  std::cout << "entt test!" << std::endl;

  entt::registry registry;

  for (auto i = 0u; i < 10u; ++i) {
    const entt::entity &entity = registry.create();
    registry.emplace<position>(entity, i * 1.f, i * 1.f);
    if (i % 2 == 0) {
      registry.emplace<velocity>(entity, i * .1f, i * .1f);
    }
  }

  update(registry);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(loop, 0, 1);
#endif

  return 0;
}