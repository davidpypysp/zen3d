#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace zen {

typedef entt::entity EntityHandle;

constexpr EntityHandle kNullEntity = entt::null;

std::string EntityToStr(EntityHandle entity);

class Scene : public entt::registry {
public:
  Scene();
};

} // namespace zen
