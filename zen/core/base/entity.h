
#pragma once

#include <vector>
#include <entt/entt.hpp>

namespace zen {

struct SceneContext{
    entt::registry registry;
};

class Entity {
public:
    Entity(SceneContext* scene_context);

private:
    SceneContext* scene_context_;

};

}

