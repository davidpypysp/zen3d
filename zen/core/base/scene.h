#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace zen {

typedef entt::entity EntityHandle;

constexpr EntityHandle kNullEntity = entt::null;

std::string EntityToStr(EntityHandle entity);

struct EntityMetadata {
  std::string name;
};

class Scene : public entt::registry {
public:
  Scene();

  EntityHandle AddEntity(const std::string& name = "");
};

} // namespace zen
