#pragma once

#include <entt/entt.hpp>
#include <vector>

namespace zen {

typedef entt::entity EntityHandle;

class Scene : public entt::registry {
public:
  Scene();
};

} // namespace zen
