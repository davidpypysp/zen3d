
#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace zen {

typedef entt::entity EntityHandle;
typedef entt::registry SceneRegistry;

struct SceneContext {
  SceneRegistry registry;
};

class Entity {
public:
  Entity(SceneContext& scene_context);

  template <typename T, typename... Args>
  void AddComponent(Args&&... args) {
    scene_context_.registry.emplace_or_replace<T>(entity_handle_,
                                                  std::forward<Args>(args)...);
  }

  template <typename T>
  void AddComponent(T&& component) {
    scene_context_.registry.emplace_or_replace<T>(entity_handle_, component);
  }

  template <typename T>
  T& GetComponent() {
    return scene_context_.registry.get<T>(entity_handle_);
  }

  const uint32_t Id() const { return (uint32_t)entity_handle_; }

private:
  SceneContext& scene_context_;
  const EntityHandle entity_handle_;
};

} // namespace zen
