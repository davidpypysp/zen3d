#pragma once

#include <vector>

#include "zen/core/base/entity.h"


namespace zen {

class Entity;

class SceneGraph {
public:
    SceneGraph();

    void CreateEntity();

private:
    SceneContext scene_context_;

    std::vector<Entity*> entities_;

    friend class Entity;
};

}
